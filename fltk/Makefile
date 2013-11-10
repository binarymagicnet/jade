all: clean fltkdemo

CMD = fltk-config
FLAGS = --libs --cxxflags --use-images --use-gl --ldstaticflags --compile

fltkdemo:
	$(CMD) $(FLAGS) $@.cpp
	
clean:
	@rm fltkdemo
	@rm -rf fltkdemo.app
    
    
