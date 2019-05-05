#ifndef HGL_GRAPH_VULKAN_BUFFER_DATA_INCLUDE
#define HGL_GRAPH_BUFFER_DATA_INCLUDE

#include"VK.h"
VK_NAMESPACE_BEGIN
    /**
        * ���������ݹ�����
        */
    class BufferData
    {
    protected:

        VkFormat    format;                                                                         ///<���ݸ�ʽ

        uint32_t    count;                                                                          ///<���ݸ���
        uint32_t    stride;                                                                         ///<���������ֽ���

        uint8_t *   buffer_data;                                                                    ///<����������
        uint32_t    total_bytes;                                                                    ///<�������ֽ���

    protected:

        friend BufferData *CreateBufferData(void *data,const VkFormat f,const uint32_t count,const uint32_t stride);

        BufferData(uint8_t *data,const VkFormat f,const uint32_t c,const uint32_t s)
        {
            buffer_data =data;

            format=f;
            count=c;
            stride=s;

            total_bytes=stride*count;
        }

    public:

        virtual ~BufferData()=default;

        uint      GetStride     ()const { return data_stride; }                                     ///<ȡ��ÿһ�������ֽ���
        uint32_t  GetCount      ()const { return data_count; }                                      ///<ȡ����������
        uint32_t  GetTotalBytes ()const { return total_bytes; }                                     ///<ȡ���������ֽ���
        void *    GetData       ()const { return buffer_data; }                                     ///<ȡ������ָ��
    };//class BufferData

    BufferData *CreateBufferData(const uint32_t &length);
    BufferData *CreateBufferData(void *data,const uint32_t &length);

    #define DATA_COMPOMENT_RED      0x01
    #define DATA_COMPOMENT_GREEN    0x02
    #define DATA_COMPOMENT_BLUE     0x04
    #define DATA_COMPOMENT_ALPHA    0x08
    #define DATA_COMPOMENT_X        DATA_COMPOMENT_RED
    #define DATA_COMPOMENT_Y        DATA_COMPOMENT_GREEN
    #define DATA_COMPOMENT_Z        DATA_COMPOMENT_BLUE
    #define DATA_COMPOMENT_W        DATA_COMPOMENT_ALPHA

    #define DATA_COMPOMENT_DEPTH    0x10

    /**
     * �Ǵ��������<Br>
     * ��������δ����������Կ���ֱ�ӶԳɷ�������һ����
     */
    class BufferDataDirect:public BufferData
    {
        VkFormat
    };//

    /**
     * ���������<Br>
     * �����������ڱ�����������޷�ֱ�ӽ��ж�д
     */
    class BufferDataPack:public BufferData
    {
        VkFormat format;                                                                            ///<���ݸ�ʽ
        uint byte;                                                                                  ///<���������ֽ���

        uint compoment;                                                                             ///<���ݳɷ�

    public:


    };//

    class VertexBufferData:public BufferData
    {
        uint32_t    data_type;                                                                      ///<������������ (GL_BYTE,GL_UNSIGNED_SHORT,GL_FLOAT��)
        uint        data_bytes;                                                                     ///<���������ֽ��� (GL_BYTEΪ1,GL_UNSIGNED_SHORTΪ2,GL_FLOATΪ4��)
        uint        data_comp;                                                                      ///<���ݳ�Ա�� (1/2/3/4����2D����������2��3D����/������3)

        uint        data_stride;                                                                    ///<ÿ�������ֽ���

        uint32_t    data_count;                                                                     ///<��������

    protected:

        friend VertexBufferData *CreateVertexBufferData(void *data,const uint32_t &dt,const uint &dbytes,const uint &dcm,const uint32_t &count);

        VertexBufferData(const uint32_t &dt,const uint &dbytes,const uint &dcm,const uint32_t &count,char *data):BufferData(data,dbytes*dcm*count)
        {
            data_type=dt;
            data_bytes=dbytes;
            data_comp=dcm;

            data_stride=data_comp*data_bytes;

            data_count=count;
        }

    public:

        virtual ~VertexBufferData()=default;

        uint32_t    GetDataType     ()const{return data_type;}                                      ///<ȡ����������
        uint        GetComponent    ()const{return data_comp;}                                      ///<ȡ��ÿһ�������е���������
        uint        GetStride       ()const{return data_stride;}                                    ///<ȡ��ÿһ�������ֽ���

        uint32_t    GetCount        ()const{return data_count;}                                     ///<ȡ����������
        uint32_t    GetTotalBytes   ()const{return total_bytes;}                                    ///<ȡ���������ֽ���
    };

    /**
        * ����һ���������ݻ�����<br>
        * ���ַ�ʽ�����Ļ��������������з����ڴ棬�����ͷ�
        * @param dt ������������ (GL_BYTE,GL_UNSIGNED_SHORT,GL_FLOAT��)
        * @param dbytes ���������ֽ��� (GL_BYTEΪ1,GL_UNSIGNED_SHORTΪ2,GL_FLOATΪ4��)
        * @param dcm ���ݳ�Ա�� (1/2/3/4����2D����������2��3D����/������3)
        * @param count ��������
        */
    VertexBufferData *CreateVertexBufferData(const uint32_t &dt,const uint &dbytes,const uint &dcm,const uint32_t &count);

    /**
        * ����һ���������ݻ�����
        * @param data ����ָ��
        * @param dt ������������ (GL_BYTE,GL_UNSIGNED_SHORT,GL_FLOAT��)
        * @param dbytes ���������ֽ��� (GL_BYTEΪ1,GL_UNSIGNED_SHORTΪ2,GL_FLOATΪ4��)
        * @param dcm ���ݳ�Ա�� (1/2/3/4����2D����������2��3D����/������3)
        * @param count ��������
        */
    VertexBufferData *CreateVertexBufferData(void *data,const uint32_t &dt,const uint &dbytes,const uint &dcm,const uint32_t &count);

#define VBDATA_CREATE_FUNC(short_name,type,comp_count,vk_type) \
    inline VertexBufferData *VB##comp_count##short_name(const uint32_t &count){return CreateVertexBufferData(vk_type,sizeof(type),comp_count,count);} \
    inline VertexBufferData *VB##comp_count##short_name(const uint32_t &count,const type *data){return CreateVertexBufferData((void *)data,vk_type,sizeof(type),comp_count,count);}

    // UNORM ָ�����޷��������Զ�ת��Ϊ 0.0 to  1.0 �ĸ�����
    // SNORM ָ�����з��������Զ�ת��Ϊ-1.0 to +1.0 �ĸ�����



#define VBDATA_NSI(comp_count,type,vk_type_start)   \
    VBDATA_CREATE_FUNC(type,comp_count,


#define VBDATA_UIF(comp_count,utype,itype,ftype,vk_type_start)    \
    VBDATA_CREATE_FUNC(u,utype,comp_count,vk_type_start);
    VBDATA_CREATE_FUNC(i,itype,comp_count,vk_type_start+1);
    VBDATA_CREATE_FUNC(f,ftype,comp_count,vk_type_start+2);

#define VBDATA_UIF_1234(utype,itype,ftype,vk_type_start)   \
    VBDATA_UIF(1,utype,itype,ftype,vk_type_start)  \
    VBDATA_UIF(2,utype,itype,ftype,vk_type_start+3)  \
    VBDATA_UIF(3,utype,itype,ftype,vk_type_start+6)  \
    VBDATA_UIF(4,utype,itype,ftype,vk_type_start+9)

    VBDATA_UIF_1234(uint32,int32,float ,VK_FORMAT_R32_UINT)
    VBDATA_UIF_1234(uint64,int64,double,VK_FORMAT_R64_UINT)
#undef VBDATA_CREATE_FUNC

    //inline VertexBufferData *EB16(const uint16 &count){return CreateVertexBufferData(GL_UNSIGNED_SHORT, 2,1,count);}
    //inline VertexBufferData *EB32(const uint32 &count){return CreateVertexBufferData(GL_UNSIGNED_INT,   4,1,count);}
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_BUFFER_DATA_INCLUDE
