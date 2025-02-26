#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <errno.h>
#include <sys/stat.h>

extern void startHelloFFmpeg(const char* file_name, void* phy_fb, int width, int height, int color_bytes);
extern void init_std_io();

static void* get_embeded_fb_in_display_app(int shared_id);
static void* get_dev_fb(char* path, int &width, int &height, int &color_bytes);

static const char* s_welcome =
"--------------------------- Help ---------------------------\n"
"Run on Linux Desktop:\n"
"./xWindow 640 360 | ./HelloFFmpeg ../test.mp4 shared-fb\n\n"

"Run on ARM Linux:\n"
"./HelloFFmpeg ../test.mp4 /dev/fb-path\n"
"------------------------------------------------------------\n";

enum FRAMEBUFFER_MODE
{
	FB_NULL_MODE,
	FB_APP_MODE,
	FB_DEV_MODE
};

int main(int argc, char** argv)
{
	printf(s_welcome);

	int color_bytes = 2;
	int screen_width = 640;
	int screen_height = 360;

	FRAMEBUFFER_MODE fb_mode = FB_NULL_MODE;
	char *fb_dev_path = NULL;
	int share_id = 1;//should be same with display app.

	const char* file_name = argv[1];
	if(!file_name)
	{
		printf("Invalide file name\n");
		return -1;
	}

	if(argc == 3)
	{
		char* argument = argv[2];
		if(strcmp(argument,"shared-fb") == 0)
		{
			fb_mode = FB_APP_MODE;
		}
		else if(strncmp(argument, "/dev", 4) == 0)
		{
			fb_dev_path = argument;
			fb_mode = FB_DEV_MODE;
		}
		else
		{
			printf("Invalid argument, should be: shared-fb, or framebuffer path\n");
			return -2;
		}
	}

	void* phy_fb = NULL;
	switch(fb_mode)
	{
		case FB_APP_MODE:
			phy_fb = get_embeded_fb_in_display_app(share_id);
		break;
		case FB_DEV_MODE:
			phy_fb = get_dev_fb(fb_dev_path, screen_width, screen_height, color_bytes);
		break;
		default:
			phy_fb = calloc(screen_width * screen_height, color_bytes);
		break;
	}

	init_std_io();
	startHelloFFmpeg(file_name, phy_fb, screen_width, screen_height, color_bytes);//never return;
    return 0;
}

static void* get_embeded_fb_in_display_app(int shared_id)
{
	void* ret = NULL;
	while(ret == NULL)
	{
		int shmid = shmget(shared_id, 0, SHM_R | SHM_W);
		if (shmid >= 0)
		{
			if(ret = (unsigned char*)shmat(shmid, 0, 0))
			{
				break;
			}
			perror("shmat failed! run display app first.\n");
		}
		else
		{
			perror("shmget failed! run display app first\n");
		}
		sleep(1);
	}
	return ret;
}

static void* get_dev_fb(char* path, int &width, int &height, int &color_bytes)
{
	int fd = open (path, O_RDWR);
	if(0 > fd)
	{
		perror("open fb failed!\n");
		_exit(-1);
	}

	struct fb_var_screeninfo vinfo;
	if (0 > ioctl(fd, FBIOGET_VSCREENINFO, &vinfo))
	{
		perror("get fb info failed!\n");
		_exit(-1);
    }

    width = vinfo.xres;
    height = vinfo.yres;
    color_bytes = vinfo.bits_per_pixel / 8;
    if (width & 0x3)
    {
        printf("Warning: vinfo.xres should be divided by 4!\nChange your display resolution to meet the rule.\n");
    }
    printf("vinfo.xres=%d\n",vinfo.xres);
    printf("vinfo.yres=%d\n",vinfo.yres);
    printf("vinfo.bits_per_pixel=%d\n",vinfo.bits_per_pixel);

	void* fbp = mmap(0, (vinfo.xres * vinfo.yres * color_bytes), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(0 > fbp)
	{
		perror("mmap fb failed!\n");  
		_exit(-1);
	}
	memset(fbp, 0, (vinfo.xres * vinfo.yres * color_bytes));
	return fbp;
}
