/* 
 * File:   File_System.h
 * Author: owenhancock
 *
 * Created on November 21, 2024, 12:38 PM
 */

#ifndef FILE_SYSTEM_H
#define	FILE_SYSTEM_H

// uint8_t mount_drive(void);

uint8_t mount_drive(FS_values_t *drive, uint8_t *array);

uint32_t first_sector(FS_values_t *drive, uint32_t cluster_num);

uint32_t find_next_clus(FS_values_t *drive, uint32_t cluster, uint8_t array[]);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* FILE_SYSTEM_H */

