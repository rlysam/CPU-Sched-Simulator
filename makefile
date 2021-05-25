#sample makefile
#hantdog
OBJS = main.o FCFS.o start.o SJF.o NPP.o SRTF.o PP.o RR.o display.o

hantdog: $(OBJS)
	g++ -o davai $(OBJS)
	
$(OBJS): myheader.h