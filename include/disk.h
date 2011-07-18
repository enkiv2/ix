#define ENFS_PARTITION_CODE 0x30
#define MAX_CYLINDERS 65535
#define HEADS_PER_CYLINDER 16
#define SECTORS_PER_TRACK 255
#define DRIVE_AND_HEAD_PORT 0x1f6
#define SECTOR_COUNT_PORT 0x1f2
#define SECTOR_NUMBER_PORT 0x1f3
#define CYLINDER_LOW_PORT 0x1f4
#define CYLINDER_HIGH_PORT 0x1f5
#define COMMAND_PORT 0x1f7
#define STATUS_PORT 0x1f7
#define DATA_PORT 0x1f0
#define COMMAND_READ_WITH_RETRY 0x20
#define COMMAND_WRITE_WITH_RETRY 0x30

typedef unsigned long  LBA;

int HD_writed(unsigned int drive, unsigned int head, unsigned long cylinder, unsigned int sector, void* data) ;
int HD_write(unsigned int drive, LBA lba, void* data, unsigned int start_head, unsigned int end_head, unsigned int start_cylinder, unsigned int end_cylinder, unsigned int start_sector, unsigned int end_sector) ;
LBA chs2lba(unsigned int head, unsigned int cylinder, unsigned int sector) ;
void* HD_readd(unsigned int drive, unsigned int head, unsigned long cylinder, unsigned int sector, unsigned int len, unsigned int start) ;
void* HD_read(unsigned int drive, LBA lba, unsigned int len, unsigned int start_head, unsigned int end_head, unsigned int start_cylinder, unsigned int end_cylinder, unsigned int start_sector, unsigned int end_sector) ;
void init() ;
void lba2chs (in LBA lba, out unsigned int head, out unsigned int cylinder, out unsigned int sector) ;
void opIndexApply(unsigned char value, unsigned long i) ;
void* opIndex(unsigned long i) ;
void opSliceAssign(void* value) ;
void opSliceAssign(void* value, unsigned long start, unsigned long end) ;
void* opSlice(unsigned long start, unsigned long end) ;
