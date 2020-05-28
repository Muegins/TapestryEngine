# Makefile

CC=g++ -g -fsanitize=address -Wno-conversion-null -Wno-pointer-arith
LDFLAGS=-lSDL2 -lcjson -lSDL2_ttf -lSDL2_mixer
INC=-ITapestryEngine

Tapestry.out: Main.o
	$(CC) -o Tapestry.out Main.o Utils.o Console.o MiscDraw.o DiagnosticDraw.o ActorCollision.o Input.o Actor.o sound.o Dialogue.o Loading.o Level.o Camera.o bones.o Event.o ActorHandle.o Animation.o AnimationGraph.o Physics.o Terrain.o HUD.o Context.o Particle.o symbol.o Mapper.o BinaryTree.o $(LDFLAGS)

ut_binarytree.out: ut_binarytree.o
	$(CC) -o ut_binarytree.out ut_binarytree.o BinaryTree.o Utils.o Console.o $(LDFLAGS)

ut_binarytree.o: Utils.o Console.o
	$(CC) -c TapestryEngine/ut_binarytree.cpp $(INC) -o ut_binarytree.o

Main.o: Utils.o Console.o MiscDraw.o DiagnosticDraw.o ActorCollision.o Input.o Actor.o sound.o Dialogue.o Loading.o Level.o
	$(CC) -c TapestryEngine/Main.cpp $(INC) -o Main.o

Utils.o: BinaryTree.o
	$(CC) -c TapestryEngine/Utils.cpp $(INC) -o Utils.o	

Console.o: Utils.o
	$(CC) -c TapestryEngine/Console.cpp $(INC) -o Console.o	

MiscDraw.o: Actor.o bones.o Camera.o Utils.o
	$(CC) -c TapestryEngine/MiscDraw.cpp $(INC) -o MiscDraw.o	

DiagnosticDraw.o: Utils.o Console.o Camera.o
	$(CC) -c TapestryEngine/DiagnosticDraw.cpp $(INC) -o DiagnosticDraw.o	

ActorCollision.o: Utils.o Console.o DiagnosticDraw.o Event.o Actor.o ActorHandle.o
	$(CC) -c TapestryEngine/ActorCollision.cpp $(INC) -o ActorCollision.o	

Input.o: Utils.o Event.o
	$(CC) -c TapestryEngine/Input.cpp $(INC) -o Input.o	

Actor.o: Utils.o Console.o Animation.o AnimationGraph.o Physics.o Terrain.o
	$(CC) -c TapestryEngine/Actor.cpp $(INC) -o Actor.o	

sound.o: Utils.o Console.o Event.o
	$(CC) -c TapestryEngine/sound.cpp $(INC) -o sound.o	

Dialogue.o: Utils.o Console.o HUD.o
	$(CC) -c TapestryEngine/Dialogue.cpp $(INC) -o Dialogue.o	

Loading.o: Utils.o Console.o Context.o Event.o
	$(CC) -c TapestryEngine/Loading.cpp $(INC) -o Loading.o	

Level.o: Utils.o Console.o Context.o Actor.o ActorCollision.o Particle.o Camera.o Event.o Input.o symbol.o MiscDraw.o sound.o HUD.o Dialogue.o
	$(CC) -c TapestryEngine/Level.cpp $(INC) -o Level.o	

Camera.o: Utils.o Console.o Actor.o Event.o
	$(CC) -c TapestryEngine/Camera.cpp $(INC) -o Camera.o	

bones.o: Utils.o Console.o
	$(CC) -c TapestryEngine/bones.cpp $(INC) -o bones.o	

Event.o: Utils.o Console.o
	$(CC) -c TapestryEngine/Event.cpp $(INC) -o Event.o	

ActorHandle.o: Utils.o Console.o Event.o Actor.o
	$(CC) -c TapestryEngine/ActorHandle.cpp $(INC) -o ActorHandle.o	

Animation.o: Utils.o Event.o
	$(CC) -c TapestryEngine/Animation.cpp $(INC) -o Animation.o	

AnimationGraph.o: Utils.o Console.o Animation.o Event.o
	$(CC) -c TapestryEngine/AnimationGraph.cpp $(INC) -o AnimationGraph.o	

Physics.o: Utils.o Console.o
	$(CC) -c TapestryEngine/Physics.cpp $(INC) -o Physics.o	

Terrain.o: Utils.o Console.o
	$(CC) -c TapestryEngine/Terrain.cpp $(INC) -o Terrain.o	
HUD.o: Utils.o Console.o Actor.o MiscDraw.o Event.o
	$(CC) -c TapestryEngine/HUD.cpp $(INC) -o HUD.o	
Context.o: Utils.o Console.o Event.o Mapper.o MiscDraw.o
	$(CC) -c TapestryEngine/Context.cpp $(INC) -o Context.o	
Particle.o: Utils.o Console.o Event.o Actor.o
	$(CC) -c TapestryEngine/Particle.cpp $(INC) -o Particle.o	
symbol.o: Utils.o Console.o Actor.o
	$(CC) -c TapestryEngine/symbol.cpp $(INC) -o symbol.o	
Mapper.o: Utils.o Console.o
	$(CC) -c TapestryEngine/Mapper.cpp $(INC) -o Mapper.o	
BinaryTree.o: 
	$(CC) -c TapestryEngine/BinaryTree.cpp $(INC) -o BinaryTree.o	
clean:
	rm  *.o*


