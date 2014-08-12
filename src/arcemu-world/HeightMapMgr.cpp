#include "Stdafx.h"

VMap::VMap(uint32 map_id)
{
	m_map_id = map_id;
	memset(&m_header,0,sizeof(VMapHeader));
	m_next_save_stamp = getMSTime() + VMAP_SAVE_INTERVAL;
	m_values_changed = 0;
	m_header.m_version = VMAP_CUR_VERSION;
	m_header.m_cell_size = sizeof( VMapCell );

	for(uint32 y=0;y<VMAP_MAX_MAP_SIZE/VMAP_SUBCELL_SIZE;y++)
		for(uint32 x=0;x<VMAP_MAX_MAP_SIZE/VMAP_SUBCELL_SIZE;x++)
			SubCellLookup[y][x] = NULL;

	//see if we already have this map and load it up
	LoadMap( false );
	//try to see if we have same map in merge directory and try to load that one into us to improve ourself
	LoadMap( true );
}

VMap::~VMap()
{
	if( m_values_changed > VMAP_SAVE_MIN_VAL_COUNT )
		SaveMap();
	for(uint32 y=0;y<VMAP_MAX_MAP_SIZE/VMAP_SUBCELL_SIZE;y++)
		for(uint32 x=0;x<VMAP_MAX_MAP_SIZE/VMAP_SUBCELL_SIZE;x++)
			if( SubCellLookup[y][x] )
			{
				free( SubCellLookup[y][x] );
				SubCellLookup[y][x] = NULL;
			}
}

void VMap::LoadMap(bool load_to_merge)
{
	char filename[150];
	VMapSubCellMaskFile *mask = NULL;
	if( load_to_merge )
		sprintf(filename,"./SVMaps/Merge/SVMap_%u.bin",m_map_id);
	else
		sprintf(filename,"./SVMaps/SVMap_%u.bin",m_map_id);
	FILE *fin=fopen(filename,"rb");
	if( fin )
	{
		int32 read_succes;

		//read the header of the map
		VMapHeader theader;
		read_succes = (int32)fread(&theader,sizeof(VMapHeader),1,fin);

		//amg file was to small ? Maybe this VMAP file is not good for us anymore ?
		if( read_succes != 1 || theader.m_version != VMAP_CUR_VERSION || theader.m_cell_size != sizeof( VMapCell ) )
			goto JUMP_ERROR;

		//in case we transmit data
		memcpy( &m_header , &theader, sizeof(VMapHeader) );

		//read the mask
		mask = (VMapSubCellMaskFile *)malloc( sizeof( VMapSubCellMaskFile ) );
		read_succes = (int32)fread(mask,sizeof(VMapSubCellMaskFile),1,fin); 

		if( read_succes != 1 )
			goto JUMP_ERROR;

		//now read the subcells based on the mask
		VMapSubCell *tsubcell = (VMapSubCell *)malloc( sizeof(VMapSubCell) );
		for(uint32 y=0;y<VMAP_MAX_MAP_SIZE/VMAP_SUBCELL_SIZE;y++)
			for(uint32 x=0;x<VMAP_MAX_MAP_SIZE/VMAP_SUBCELL_SIZE;x++)
				if( mask->SubCellMask[y][x] != 0 )
				{
					//get pointer to a new or existing subcell
					VMapSubCell *newcell;
					if( SubCellLookup[y][x] == NULL )
					{
						newcell = (VMapSubCell*)malloc( sizeof(VMapSubCell) );
						//would be great to check this is if it is NULL. The whole thing will crash if null though
						memset( newcell, 0, sizeof( VMapSubCell ) );
					}
					else 
						newcell = SubCellLookup[y][x];
					if( !newcell )
						goto JUMP_ERROR;	//no frikkin way
					//read values in temporal value
					read_succes = (int32)fread(tsubcell,sizeof(VMapSubCell),1,fin); 
					if( read_succes != 1 )
						goto JUMP_ERROR;	//early EOF ?
					//merge values
					for(uint32 y1=0;y1<VMAP_SUBCELL_SIZE;y1++)
						for(uint32 x1=0;x1<VMAP_SUBCELL_SIZE;x1++)
						{
							VMapCell *tcell = &tsubcell->SubCell[ y1 ][ x1 ];
							VMapCell *dcell = &newcell->SubCell[ y1 ][ x1 ];
							//simple import
							if( tcell->floor_sums[0] != 0 && dcell->floor_sums_count[0] == 0 )
								memcpy( dcell, tcell, sizeof( VMapCell ) );
							//if we have something to import and destination also has values
							else if( tcell->floor_sums[0] )
							{
								dcell->floor_sums[0] = (dcell->floor_sums[0] + tcell->floor_sums[0]) / 2;
//								dcell->floor_sums[1] = (dcell->floor_sums[1] + tcell->floor_sums[1]) / 2;

								dcell->floor_sums_count[0] = (dcell->floor_sums_count[0] + tcell->floor_sums_count[0] + 1 ) / 2;
//								dcell->floor_sums_count[1] = (dcell->floor_sums_count[1] + tcell->floor_sums_count[1] + 1 ) / 2;
							}
						}
					//store if there was a new subcell or restore old one
					SubCellLookup[y][x] = newcell;
				}
		free( tsubcell );
		tsubcell = NULL;
		//done loading
		fclose(fin);
		fin = NULL;

		//delete the file
		if( load_to_merge )
			_unlink( filename );
	}
	if( fin )
	{
JUMP_ERROR:
		memset(&m_header,0,sizeof(VMapHeader));
		fclose(fin);
	}
	if( mask )
		free( mask );
}

void VMap::SaveMap()
{
	char filename[50];
	VMapSubCellMaskFile *mask = NULL;
	sprintf(filename,"./SVMaps/SVMap_%u.bin",m_map_id);
	FILE *fout=fopen(filename,"wb");
	if( fout )
	{
		//write header
		fwrite(&m_header,sizeof(VMapHeader),1,fout);

		//create and write a mask
		mask = (VMapSubCellMaskFile *)malloc( sizeof( VMapSubCellMaskFile ) );
		for(uint32 y=0;y<VMAP_MAX_MAP_SIZE/VMAP_SUBCELL_SIZE;y++)
			for(uint32 x=0;x<VMAP_MAX_MAP_SIZE/VMAP_SUBCELL_SIZE;x++)
				if( SubCellLookup[y][x] != 0 )
					mask->SubCellMask[y][x] = 1;
				else
					mask->SubCellMask[y][x] = 0;
		fwrite(mask,sizeof(VMapSubCellMaskFile),1,fout);

		//now write subcells
		for(uint32 y=0;y<VMAP_MAX_MAP_SIZE/VMAP_SUBCELL_SIZE;y++)
			for(uint32 x=0;x<VMAP_MAX_MAP_SIZE/VMAP_SUBCELL_SIZE;x++)
				if( SubCellLookup[y][x] != 0 )
					fwrite(SubCellLookup[y][x],sizeof(VMapSubCell),1,fout);
		fclose(fout);
	}
	if( mask )
		free( mask );
}

VMapCell *VMap::getCellForWoWCords(float x, float y)
{
	int32 scaled_x = (int32)x / VMAP_SCALE_WOW_MAP_RES;
	int32 scaled_y = (int32)y / VMAP_SCALE_WOW_MAP_RES;

	uint32 centered_scaled_x = VMAP_MAP_SIZE_HALF + scaled_x;
	uint32 centered_scaled_y = VMAP_MAP_SIZE_HALF + scaled_y;

	uint32 subcell_x = centered_scaled_x / VMAP_SUBCELL_SIZE;
	uint32 subcell_y = centered_scaled_y / VMAP_SUBCELL_SIZE;

	if( centered_scaled_x >= VMAP_MAX_MAP_SIZE || centered_scaled_x < 0 )
		return NULL;

	if( centered_scaled_y >= VMAP_MAX_MAP_SIZE || centered_scaled_x < 0 )
		return NULL;

	uint32 cell_x = centered_scaled_x % VMAP_SUBCELL_SIZE;
	uint32 cell_y = centered_scaled_y % VMAP_SUBCELL_SIZE;

	//check if we have it yet. If not then create a new one
	if( SubCellLookup[ subcell_y ][ subcell_x ] == NULL )
	{
		SubCellLookup[ subcell_y ][ subcell_x ] = (VMapSubCell*)malloc( sizeof(VMapSubCell) );
		//would be great to check this is if it is NULL. The whole thing will crash if null though
		memset( SubCellLookup[ subcell_y ][ subcell_x ], 0, sizeof( VMapSubCell ) );
	}

	return &SubCellLookup[ subcell_y ][ subcell_x ]->SubCell[ cell_y ][ cell_x ];
}

void VMap::AddSample(float x, float y, float z)
{
	//invalid value
	if( z < VMAP_VALUE_BOTTOM_OF_THE_OCEAN || z > VMAP_VALUE_FAR_IN_THE_SKY )
		return;

	VMapCell *cell = getCellForWoWCords(x, y);

	if( cell == NULL )
		return;

	//avoid inserting values into map that would let players fall trough the map
	signed short sz = (signed short)(z + VMAP_SAFETY_ERROR_CORRECTION);

	//if value is smaller then theoretic floor 1 then store it
	if( cell->floor_sums_count[0] < VMAP_STABLE_STATISTIC_VALUE && (cell->floor_sums[0] < 10 
//		|| sz + VMAP_FLOOR_MIN_DISTANCE <= cell->floor_sums[0] / cell->floor_sums_count[0] 
		//required to not save values produced by underground falls or WPE hack : port to plane
		|| sz >= cell->floor_sums[0] / cell->floor_sums_count[0]
	) )
	{
		cell->floor_sums[0] += sz;
		cell->floor_sums_count[0]++;
		m_values_changed++;
	}

/*	//if value is larger then theoretic floor 0 then store it
	if( cell->floor_sums_count[1] < VMAP_STABLE_STATISTIC_VALUE && ( cell->floor_sums[1] == 0 || sz - VMAP_FLOOR_MIN_DISTANCE >= cell->floor_sums[1] / cell->floor_sums_count[1] ) )
	{
		cell->floor_sums[1] += sz;
		cell->floor_sums_count[1]++;
		m_values_changed++;
	}*/

	//periodically save maps without spamming HD
	if( m_values_changed > VMAP_SAVE_MIN_VAL_COUNT && m_next_save_stamp < getMSTime() )
	{
		m_next_save_stamp = getMSTime() + VMAP_SAVE_INTERVAL;
		m_values_changed = 0;
		SaveMap();
	}
}

float VMap::GetHeight(float x, float y, float z)
{
	//get the cell we will work with
	VMapCell	*cell = getCellForWoWCords(x, y);

	if( cell == NULL )
		return VMAP_VALUE_NOT_INITIALIZED;

	float val1;
	if( cell->floor_sums_count[0] )
		val1 = (float)cell->floor_sums[0] / cell->floor_sums_count[0];
	else
		val1 = VMAP_VALUE_NOT_INITIALIZED;

	//lowest floor if neighbour is not provided
/*	
	float val2;
	if( z == VMAP_VALUE_NOT_INITIALIZED )
		return val1;

	if( cell->floor_sums_count[1] )
		val2 = (float)cell->floor_sums[1] / cell->floor_sums_count[1];
	else
		val2 = VMAP_VALUE_NOT_INITIALIZED;

	float dist1,dist2;
	dist1 = abs(val1 - z);
	dist2 = abs(val2 - z);
	if( dist1 < dist2 )
		return val1;

	return val2;*/

	return val1;	//right now we use on 1 floor
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//						this is the manager for the VSmaps
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

VMapMgr::VMapMgr()
{
	//right now create maps for BG only
/*	m_vmaps[ 30 ] = new VMap( 30 );		//Alterac Valley
	m_vmaps[ 37 ] = new VMap( 37 );		//Azshara Crater
	m_vmaps[ 489 ] = new VMap( 489 );	//Warsong Gulch
	m_vmaps[ 529 ] = new VMap( 529 );	//Arathi Basin
	m_vmaps[ 559 ] = new VMap( 559 );	//Nagrand Arena
	m_vmaps[ 566 ] = new VMap( 566 );	//Eye of the Storm
	m_vmaps[ 607 ] = new VMap( 607 );	//Strand of the Ancients

	//northshire abbey has more then 1 level
	m_vmaps[ 0 ] = new VMap( 0 );	*/
}

VMapMgr::~VMapMgr()
{
	std::map<uint32,VMap *>::iterator itr;
	for( itr = m_vmaps.begin(); itr != m_vmaps.end(); itr++)
		delete itr->second;
	m_vmaps.clear();
}

void VMapMgr::AddSample(uint32 map,float x, float y, float z)
{
	if( m_vmaps[ map ] )
		m_vmaps[ map ]->AddSample(x, y, z);
	else 
	{
		m_vmaps[ map ] = new VMap( map );
		m_vmaps[ map ]->AddSample(x, y, z);
	}
}

float VMapMgr::GetHeight(uint32 map,float x, float y, float z)
{
	if( m_vmaps[ map ] )
		return m_vmaps[ map ]->GetHeight(x, y, z);

	return VMAP_VALUE_NOT_INITIALIZED;
}

initialiseSingleton( VMapMgr );