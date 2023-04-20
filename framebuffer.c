/*
Framebuffer template program
Run this and the screen goes blank for 2 seconds, then comes back.
*/
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>	/* for mmap */
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char *fbp; // pointer to framebuffer (upper left corner)
char *backp; // screen backup area
uint32_t screenbytes; // screen size in bytes (authoritative)
uint32_t screenstride; // bytes for each scanline of full screen
uint32_t yres; // vertical screen resolution
uint32_t xres; // horizontal screen resolution
uint32_t bpp; // bytes per pixel
uint32_t bitsperpixel; // sometimes you need bits, sometimes bytes
uint32_t speccolor = 0x01f5f600; // Tektronix scope blue pixel at 32 bpp

void
restore_screen(void)
{ // copy back
	memcpy(fbp,backp,screenbytes);
}

void
fbinit(void)
{ // set up framebuffer, back up screen area
	struct fb_var_screeninfo vinfo; // fetched with an ioctl
	struct fb_fix_screeninfo finfo; // this has smem_len: screen bytes
	int fbfd; // frame buffer file descriptor
	fbfd = open("/dev/fb0", O_RDWR);
	if (fbfd == -1) {
		fprintf(stderr, "Error opening /dev/fb0\n");
		perror("open ");
		exit(1);
	}
	// get the fixed screen information
	if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
		printf("Error reading fixed information.\n");
		exit(2);
	}
	// get variable screen info
	// each struct (FSCREENINFO and VSCREENINFO) has unique and useful numbers
	if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
		fprintf(stderr, "Error reading variable screen info struct.\n");
		exit(3);
	}
	xres = vinfo.xres;
	yres = vinfo.yres;
	bpp = vinfo.bits_per_pixel / 8;  
	bitsperpixel = vinfo.bits_per_pixel;
	printf("Screen is %u x %u, %u bytes/pixel\n", xres, yres, bpp);
	screenstride = finfo.line_length;
	screenbytes = finfo.smem_len;
	backp = malloc(screenbytes);
	if (backp == NULL) {
		fprintf(
			stderr, "Can't malloc %u bytes to back up screen\n", screenbytes);
		exit(1);
	}
	fbp = mmap(
		NULL, finfo.smem_len, 
		PROT_READ|PROT_WRITE, MAP_SHARED, 
		fbfd, 0);
	if (fbp < 0) { // returns (void *) -1 on error
		fprintf(stderr, "mmap failed\n");
		perror("mmap ");
		exit(1);
	}
	close(fbfd); // don't need anymore
	memcpy(backp, fbp, screenbytes); // back up screen
	bzero(fbp, screenbytes); // fill screen with black
}


int
main(void)
{
	fbinit();
	sleep(2); // simulate doing something, call your function here
	restore_screen();
	free(backp);
	munmap(fbp, screenbytes);
	return 0;
}
