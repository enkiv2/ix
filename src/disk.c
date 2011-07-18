/*	disk.c
 *	(c) 2007-2010 John Ohno
 *	Licensed under the GNU LGPL
 */

#include <disk.h>

typedef unsigned long  LBA;

void* HD_readd(unsigned int drive, unsigned int head, unsigned long cylinder, unsigned int sector, unsigned int len, unsigned int start=0) {
	unsigned char* buf;
	unsigned char temp;
	outportb(DRIVE_AND_HEAD_PORT, (char)((drive<<4)|head));
	outportb(SECTOR_COUNT_PORT, (char)len);
	outportb(SECTOR_NUMBER_PORT, (char)sector);
	outportb(CYLINDER_LOW_PORT, ((char)cylinder));
	outportb(CYLINDER_HIGH_PORT, ((char)(cylinder>>8)));
	outportb(COMMAND_PORT, COMMAND_READ_WITH_RETRY);
	for (int i=0; i<start; i++) {
		while (inportb(COMMAND_PORT)&255) {}
		inportb(DATA_PORT);
	}
	for (int i=0; i<len; i++) {
		while (inportb(COMMAND_PORT)&255){}
		temp=inportb(DATA_PORT);
		if (!(inportb(STATUS_PORT)&1)) {
			buf~=temp;
		}
	}
	return  buf;
}

int HD_writed(unsigned int drive, unsigned int head, unsigned long cylinder, unsigned int sector, void* data) {
	int i=0;
	outportb(DRIVE_AND_HEAD_PORT, (unsigned char)((drive<<4)|head));
	outportb(SECTOR_COUNT_PORT, (unsigned char)data.length);
	outportb(SECTOR_NUMBER_PORT, (unsigned char)sector);
	outportb(CYLINDER_LOW_PORT, ((unsigned char) cylinder));
	outportb(CYLINDER_HIGH_PORT, ((unsigned char)(cylinder>>8)));
	outportb(COMMAND_PORT, COMMAND_WRITE_WITH_RETRY);
	for (i=0; i<data.length; i++) {
		while (inportb(COMMAND_PORT)&255) {}
		outportb(DATA_PORT, (unsigned char)data[i]);
		if (inportb(STATUS_PORT)&1) { return -1; }
	}
	return 0;
}

int HD_write(unsigned int drive, LBA lba, void* data, unsigned int start_head=0, unsigned int end_head=HEADS_PER_CYLINDER, unsigned int start_cylinder=0, unsigned int end_cylinder=MAX_CYLINDERS, unsigned int start_sector=0, unsigned int end_sector=SECTORS_PER_TRACK) {
	unsigned int head;
	unsigned int cylinder;
	unsigned int sector;
	lba2chs (lba/512, head, cylinder, sector);
	unsigned int start=((lba/MAX_CYLINDERS)/HEADS_PER_CYLINDER)%512;
	head+=start_head;
	cylinder+=start_cylinder;
	sector+=start_sector;
	if (head<=end_head && cylinder <= end_cylinder && sector <= end_sector) {
		void* temp=HD_readd(drive, head, cylinder, sector, 512);
		temp[start .. start+data.length]=data;
		return HD_writed (drive, head, cylinder, sector, temp);
	}
	return -1;
}

void* HD_read(unsigned int drive, LBA lba, unsigned int len, unsigned int start_head=0, unsigned int end_head=HEADS_PER_CYLINDER, unsigned int start_cylinder=0, unsigned int end_cylinder=MAX_CYLINDERS, unsigned int start_sector=0, unsigned int end_sector=SECTORS_PER_TRACK) {
	unsigned int head;
	unsigned int cylinder;
	unsigned int sector;
	lba2chs (lba/512, head, cylinder, sector);
	unsigned int start=((lba/MAX_CYLINDERS)/HEADS_PER_CYLINDER)%512;
	head+=start_head;
	cylinder+=start_cylinder;
	sector+=start_sector;
	if (head <= end_head && cylinder <= end_cylinder && sector <= end_sector) {
		return HD_readd(drive, head, cylinder, sector, len)[start .. start+length];
	}
	unsigned char* x;
	return x;
}

LBA chs2lba(unsigned int head, unsigned int cylinder, unsigned int sector) {
	return (((cylinder * HEADS_PER_CYLINDER + head) * SECTORS_PER_TRACK) + sector) -1;
}

void lba2chs (in LBA lba, out unsigned int head, out unsigned int cylinder, out unsigned int sector) {
	cylinder=lba/(HEADS_PER_CYLINDER * SECTORS_PER_TRACK);
	unsigned int temp=lba%(HEADS_PER_CYLINDER * SECTORS_PER_TRACK);
	head=temp/SECTORS_PER_TRACK;
	sector=temp%SECTORS_PER_TRACK + 1;
}

struct MMDisk {
	unsigned long size;
	unsigned char drive=0x0a;
	unsigned long len;
	void init() {
		len=size;
	}
	void* opIndex(unsigned long i) {
		if (i>size) {
			return null;
		}
		return &(HD_read(drive, i, 1)[0]);
	}
	void opIndexApply(unsigned char value, unsigned long i) {
		if (i<=size) {
			unsigned char* temp;
			temp[0]=value;
			HD_write(drive, i, temp);
		}
	}
	void* opSlice(unsigned long start, unsigned long end) {
		return HD_read(drive, start, end-start);
	}
	void opSliceAssign(void* value, unsigned long start, unsigned long end) {
		if ((end-start)!=value.length) {
			HD_write(drive,start+value.length, HD_read(drive, start, value.length+(size-(end-start))-start)); // Move stuff over
		}
		HD_write(drive, start, value);
	}
	void opSliceAssign(void* value) {
		opSliceAssign(value, 0, size);
	}
}

struct MMPart {
	unsigned long size;
	unsigned char drive=0x0a;
	unsigned int partnumber=0; // 0-3
	bool bootable;
	unsigned long start_cylinder;
	unsigned char start_sector;
	unsigned long end_cylinder;
	unsigned char end_sector;
	unsigned char start_head;
	unsigned char end_head;
	unsigned char fs_type;
	unsigned long len;
	void init() {
		bootable=(((unsigned char)HD_read(drive, 446, 1)[0])==0x80);
		start_head=((unsigned char*)HD_read(drive, 446+1, 1))[0];
		end_head=((unsigned char*)HD_read(drive, 446+5, 1))[0];
		unsigned char* temp=(unsigned char*)(HD_read(drive, 446+2, 2));
		temp~=(unsigned char*)(HD_read(drive, 446+6, 2));
		start_cylinder=((((unsigned int)temp[0])<<8)|((unsigned int)temp[1]));
		start_sector=(temp[0]&0x1F);
		end_cylinder=((((unsigned int)temp[2])<<8)|((unsigned int)temp[3]));
		end_sector=(temp[2]&0x1F);
		fs_type=((unsigned char*)HD_read(drive, 446+4, 1))[0];
		len=size;
	}
	void* opIndex(unsigned long i) {
		return &(HD_read(drive, i, 1, start_head, end_head, start_cylinder, end_cylinder, start_sector, end_sector)[0]);
	}
	void opIndexApply(unsigned char value, unsigned long i) {
		unsigned char* temp;
		temp[0]=value;
		HD_write(drive, i, (void*)temp, start_head, end_head, start_cylinder, end_cylinder, start_sector, end_sector);
	}
	void* opSlice(unsigned long start, unsigned long end) {
		return HD_read(drive, start, end-start, start_head, end_head, start_cylinder, end_cylinder, start_sector, end_sector);
	}
	void opSliceAssign(void* value, unsigned long start, unsigned long end) {
		if ((end-start) != value.length) {
			HD_write(drive, start+value.length, HD_read(drive, start, value.length+(size-(end-start)+start), start_head, end_head, start_cylinder, end_cylinder, start_sector, end_sector), start_head, end_head, start_cylinder, end_cylinder, start_sector, end_sector);
		}
		HD_write(drive, start, value, start_head, end_head, start_cylinder, end_cylinder, start_sector, end_sector);
	}
	void opSliceAssign(void* value) {
		opSliceAssign(value, 0, size);
	}
}

