#ifndef __VBM_H__
#define __VBM_H__

#include "vgl.h"

typedef struct VBM_HEADER_t
{
    unsigned int magic;
    unsigned int size;
    char name[64];
    unsigned int num_attribs;
    unsigned int num_frames;
    unsigned int num_vertices;
    unsigned int num_indices;
    unsigned int index_type;
} VBM_HEADER;

typedef struct VBM_ATTRIB_HEADER_t
{
    char name[64];
    unsigned int type;
    unsigned int components;
    unsigned int flags;
} VBM_ATTRIB_HEADER;

typedef struct VBM_FRAME_HEADER_t
{
    unsigned int first;
    unsigned int count;
    unsigned int flags;
} VBM_FRAME_HEADER;

typedef struct VBM_VEC4F_t
{
    float x;
    float y;
    float z;
    float w;
} VBM_VEC4F;

class VBObject
{
public:
    VBObject(void);
    virtual ~VBObject(void);

    bool LoadFromVBM(const char * filename, int vertexIndex, int normalIndex, int texCoord0Index);
    void Render(unsigned int frame_index = 0, unsigned int instances = 0);
    bool Free(void);

    unsigned int GetVertexCount(unsigned int frame = 0)
    {
        return frame < m_header.num_frames ? m_frame[frame].count : 0;
    }

    unsigned int GetAttributeCount(void) const
    {
        return m_header.num_attribs;
    }

    const char * GetAttributeName(unsigned int index) const
    {
        return index < m_header.num_attribs ? m_attrib[index].name : 0;
    }

    void BindVertexArray()
    {
        glBindVertexArray(m_vao);
    }

protected:
    GLuint m_vao;
    GLuint m_attribute_buffer;
    GLuint m_index_buffer;

    VBM_HEADER m_header;
    VBM_ATTRIB_HEADER * m_attrib;
    VBM_FRAME_HEADER * m_frame;
};

#endif /* __VBM_H__ */
