﻿#include<hgl/io/FileAccess.h>
#include<hgl/LogInfo.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>

namespace hgl
{
	namespace io
	{
		bool FileAccess::CreateTemp()
		{
			char template_filename[HGL_MAX_PATH]="/tmp/cm/XXXXXX";

			fp=mkstemps(template_filename,HGL_MAX_PATH);

			if(fp==-1)
				return(false);

			filename=template_filename;
			mode=fomCreate;

			return(true);
        }

		int OpenFile(const os_char *fn,FileOpenMode fom)
        {
            int fp;

			if(fom==fomCreate		)fp=hgl_open64(fn,O_WRONLY|O_CREAT,           S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);else
			if(fom==fomCreateTrunc	)fp=hgl_open64(fn,O_WRONLY|O_CREAT|O_TRUNC,   S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);else
			if(fom==fomOnlyRead		)fp=hgl_open64(fn,O_RDONLY	);else
			if(fom==fomOnlyWrite	)fp=hgl_open64(fn,O_WRONLY	);else
			if(fom==fomReadWrite	)fp=hgl_open64(fn,O_RDWR	);else
			if(fom==fomAppend		)fp=hgl_open64(fn,O_APPEND	);else
            {
                LOG_ERROR(OS_TEXT("UNIX,FileAccess,OpenFile(")+OSString(fn)+OS_TEXT(" mode error: "+OSString(fom)));
                RETURN_ERROR(-1);
            }

            if(fp==-1)
            {
                LOG_ERROR(OS_TEXT("UNIX,FileAccess,OpenFile(")+OSString(fn)+OS_TEXT(") open return error: "+OSString(errno)));
            }

            return fp;
        }

        void CloseFile(int fp)
        {
			close(fp);
        }

		int64 FileAccess::Read(int64 offset,void *buf,int64 size)
		{
			if(!CanRead())return(-1);

			return hgl_pread64(fp,buf,size,offset);
		}

		int64 FileAccess::Write(int64 offset,const void *buf,int64 size)
		{
			if(!CanWrite())return(-1);

			return hgl_pwrite64(fp,buf,size,offset);
		}
	}//namespace io
}//namespace hgl
