struct CommunicationBuffer
{ 
   size_t size;
   char * buffer;
};

struct CommunicationBuffer* allocateCommunicationBuffer(struct CommunicationBuffer *commBuf){
    commBuf->buffer = (char *)calloc(commBuf->size, sizeof(char));
    return commBuf;
}

char* expandBuf(struct CommunicationBuffer *commBuf){
    size_t old_buf_size = commBuf->size;
    commBuf->size = 2*(commBuf->size);
    commBuf->buffer = (char *)realloc(commBuf->buffer, sizeof(char)*commBuf->size);
}
