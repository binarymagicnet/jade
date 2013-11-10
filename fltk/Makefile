all: clean fltkdemo

CMD = fltk-config
FLAGS = --libs --cxxflags --use-images --use-gl --ldstaticflags --compile

fltkdemo:
	$(CMD) $(FLAGS) $@.cpp
	
clean:
	@rm -f fltkdemo
	@rm -rf fltkdemo.app
    
    
