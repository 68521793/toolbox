target=testMessageReceiver
obj=src/MessageReceiver.o src/CANTransceiver.o test/testReceiver.o
$(target):$(obj)
	g++ $^ -I include -o $@
%.o:%.cpp
	g++ -c -I include $< -o $@
clean:
	rm $(target) $(obj)