///*
// * File:   DoubleBuffer.h
// * Author: malcom
// *
// * Created on August 28, 2013, 3:30 PM
// */
//
//#ifndef DOUBLEBUFFER_H
//#define	DOUBLEBUFFER_H
//
//#define DOUBLE_BUFFER_SIZE 150
//
//struct _Buffer
//{
//  char payload[DOUBLE_BUFFER_SIZE] ;
//  char* start;
//  char* end;
//  char* curr;
//} b1,b2;
//
//struct _DoubleBuffer
//{
//    struct _Buffer* readingBuffer;
//    struct _Buffer* parsingBuffer;
//    struct _Buffer* _BufferContainer[2];
//
//    int state;
//
//} DoubleBuffer;
//
//
//
//
//void DoubleBuffer_Init()
//{
//    DoubleBuffer._BufferContainer[0]=&b1;
//    DoubleBuffer._BufferContainer[1]=&b2;
//    DoubleBuffer.readingBuffer=DoubleBuffer._BufferContainer[0];
//    DoubleBuffer.parsingBuffer=DoubleBuffer._BufferContainer[1];
//
//
//    DoubleBuffer.readingBuffer->start=DoubleBuffer.readingBuffer->payload;
//    DoubleBuffer.readingBuffer->end=DoubleBuffer.readingBuffer->start+sizeof(char)*DOUBLE_BUFFER_SIZE;
//    DoubleBuffer.readingBuffer->curr=DoubleBuffer.readingBuffer->start;
//
//    DoubleBuffer.parsingBuffer->start=DoubleBuffer.parsingBuffer->payload;
//    DoubleBuffer.parsingBuffer->end=DoubleBuffer.parsingBuffer->start+sizeof(char)*DOUBLE_BUFFER_SIZE;
//    DoubleBuffer.parsingBuffer->curr=DoubleBuffer.parsingBuffer->start;
//
//    DoubleBuffer.state=0;
//
//}
//
//void DoubleBuffer_swapBuffers()
//{
//    if(DoubleBuffer.state)
//    {
//        DoubleBuffer.readingBuffer=DoubleBuffer._BufferContainer[0];
//        DoubleBuffer.parsingBuffer=DoubleBuffer._BufferContainer[1];
//        DoubleBuffer.state=0;
//    }
//    else
//    {
//        DoubleBuffer.readingBuffer=DoubleBuffer._BufferContainer[1];
//        DoubleBuffer.parsingBuffer=DoubleBuffer._BufferContainer[0];
//        DoubleBuffer.state=1;
//    }
//}
//
//void DoubleBuffer_resetReadingBuffer()
//{
//    DoubleBuffer.readingBuffer->start=DoubleBuffer.readingBuffer->payload;
//    DoubleBuffer.readingBuffer->end=DoubleBuffer.readingBuffer->start+sizeof(char)*DOUBLE_BUFFER_SIZE;
//    DoubleBuffer.readingBuffer->curr=DoubleBuffer.readingBuffer->start;
//}
//
//void DoubleBuffer_resetParsingBuffer()
//{
//    DoubleBuffer.parsingBuffer->start=DoubleBuffer.parsingBuffer->payload;
//    DoubleBuffer.parsingBuffer->end=DoubleBuffer.parsingBuffer->start+sizeof(char)*DOUBLE_BUFFER_SIZE;
//    DoubleBuffer.parsingBuffer->curr=DoubleBuffer.parsingBuffer->start;
//}
//
//
//#endif	/* DOUBLEBUFFER_H */
//
