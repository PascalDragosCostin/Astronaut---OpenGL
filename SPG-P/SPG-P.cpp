#include <iostream>
#include <SDL2/SDL.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

#define PI 3.1415f


// static, deci pot accesa doar in acest fisier datele astea
static const int DISPLAY_WIDTH = 1280;
static const int DISPLAY_HEIGHT = 720;


// error LNK2019: unresolved external symbol _SDL_main referenced in function _main  daca folosesc doar main()
int main(int argc, char* argv[])

{
    std::cout << "Starts!\n";
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Proiect SPG");

	Vertex vertices[] =
	{
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1)),

		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0)),

		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0)),

		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0)),
	};

	unsigned int indices[] = { 0, 1, 2,
							  0, 2, 3,

							  6, 5, 4,
							  7, 6, 4,

							  10, 9, 8,
							  11, 10, 8,

							  12, 13, 14,
							  12, 14, 15,

							  16, 17, 18,
							  16, 18, 19,

							  22, 21, 20,
							  23, 22, 20
	};



	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Mesh astronaut("./res/astronaut_mini.obj");
	//Mesh monkey("./res/monkey3.obj");


	// Incarca vertex shader si fragment shader
	Shader shader("./res/shader");
	
	Texture texture("./res/bricks.jpg");  
	//Texture texture("./res/ciment.jpg");  
	//Texture texture("./res/marble.jpg");  


	// Transform transform(glm::vec3(0, -15, 15), glm::vec3(-90, 0, 0), glm::vec3(0.1f, 0.1f, 0.1f));
	//Transform transform;
	//Transform transformMonkey(glm::vec3(0, 0, 0), glm::vec3(180, 0, 180), glm::vec3(1.0f, 1.0f, 1.0f));


	Transform transformMonkey(glm::vec3(0, -4, 15), glm::vec3(0, 180, 0), glm::vec3(0.05f, 0.05f, 0.05f));
	
	Camera camera(glm::vec3(0.0f, 0.0f, -10.0f), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);

	SDL_Event e;
	bool isRunning = true;

	shader.Bind();
	texture.Bind();

	float counter = PI/2;
	float initialX = transformMonkey.GetPosAbsolute().x;
	float initialY = transformMonkey.GetPosAbsolute().y;
	float initialZ = transformMonkey.GetPosAbsolute().z;
	float initialRX = transformMonkey.GetRot()->x;
	float initialRZ = transformMonkey.GetRot()->z;
	
	float speed = 0.001;

	while (isRunning)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				isRunning = false;
		}

		//display.Clear(0.025f, 0.025f, 0.05f, 1.0f);  // un gri albastrui 
		display.Clear(0.1f, 0.1f, 0.2f, 1.0f);  // un gri albastrui mai deschis

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);
		float cosCounterDefazat = cosf(counter - PI/2);
		//float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);


		transformMonkey.GetPos()->x = initialX + cosCounter * 15;
		transformMonkey.GetPos()->y = initialY + cosCounter * sinCounter * 15;
		transformMonkey.GetPos()->z = initialZ + cosCounterDefazat * 12 ;
		transformMonkey.GetRot()->y = (-counter * 2 - 90) * 25;
		transformMonkey.GetRot()->z = sin(initialRZ + counter) * 3 ;

		
		/*float absSinCounter = abs(sinCounter);*/
		//transform.GetPos()->z = transform.GetPos()->z - counter/100;
		//transformMonkey.GetRot()->y = counter * 10;
		//transformMonkey.GetRot()->x = counter * 10;
		/*transform.GetScale()->x = absSinCounter;
		transform.GetScale()->y = absSinCounter;*/


		shader.Update(transformMonkey, camera);
		astronaut.Draw();
		//mesh.Draw();

		display.SwapBuffers();
		SDL_Delay(1);
		counter += speed;

		//std::cout << counter << std::endl;
	/*	if (fabs(counter - 5) < 0.01)
		{
			speed = -speed;
		}*/
	}

    return 0;
}

