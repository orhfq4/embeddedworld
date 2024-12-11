#include "Drive_Values.h"


FS_values_t drive_values;

/***********************************************************************
DESC: Returns a pointer to the global structure Drive_values to export to other files
INPUT: void
RETURNS: Pointer to the structure Drive_values
CAUTION: 
************************************************************************/

FS_values_t * export_drive_values(void)
{
   return &drive_values;
}


