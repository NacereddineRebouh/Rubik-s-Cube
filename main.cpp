#define GLFW_DLL
#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include "glad.c"
#include <shader.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtx/string_cast.hpp>
#include<string>
#include<time.h>
#include <gtx/transform.hpp>
#include <iostream>
#include "stb/stb_image.h"


#define 	GLFW_MOD_SHIFT   0x0001
// 	If this bit is set one or more Shift keys were held down. More...

#define 	GLFW_MOD_CONTROL   0x0002
// 	If this bit is set one or more Control keys were held down. More...

#define 	GLFW_MOD_ALT   0x0004
// 	If this bit is set one or more Alt keys were held down. More...

#define 	GLFW_MOD_SUPER   0x0008
// 	If this bit is set one or more Super keys were held down. More...

#define 	GLFW_MOD_CAPS_LOCK   0x0010
// 	If this bit is set the Caps Lock key is enabled. More...

#define 	GLFW_MOD_NUM_LOCK   0x0020

using namespace glm;
using namespace std;
void Resize(GLFWwindow* window, int width, int height)
 {
    glViewport(0, 0, width, height);
 }

struct STRVertex
{
 vec3 position;
 vec3 couleur;
 vec2 coords;
 vec3 normal;
};
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void scroll_callback(GLFWwindow *window,double xoffset, double yoffset);
void glfwGetCursorPos ( GLFWwindow* window, double xpos, double ypos);
void mouse_button (GLFWwindow* window, int button, int action, int mods);
int random(int min, int max);
void randomizeCube(vec3 instancesPositions[]);
//camera vectors
vec3 cameraPos=vec3(0.0f,0.0f,50.0f);
vec3 cameraOrigin=vec3(0.0f,0.0f,0.0f);
vec3 cameraUp=vec3(0.0f,1.0f,0.0f);

float fov=20.0f;
//mouvements
float velocity=0.009;

float diffX=0;
float diffY=0;
float rotX=0;
float rotY=0;
float rotCol=0;
float rotRow=0;
float rotX1=0;
float rotX2=0;
float rotX3=0;
float rotY1=0;
float rotY2=0;
float rotY3=0;
float rotationX=0;
float rotationY=0;
float rotationX1=0;
float rotationX2=0;
float rotationX3=0;
float rotationY1=0;
float rotationY2=0;
float rotationY3=0;
float initRot=0.5;
float initRotEase=0.1;
double Xpos=0, Ypos=0;
float Modelscale=1;
float delai=200;
int width, height;
bool GlobalRotation=false;
string LastRotated="X";
string LastRowColRotated="none";
struct Rotation {
    string XY;
    float angle;
    vec3 Vec;
    vec3 Vec2;
};
bool done=false;
bool canReset=true;
bool fixedRotY=true;
bool fixedRotX=true;
bool fixedRowRot=true;
bool fixedColRot=true;
bool decided=false;
mat4 Models[100];
mat4 saveInitialState[100];
bool Win = false;
int sizeRot=0;
int sizeModels=0;
Rotation Rotations[100];
string rotationRoCol="none";

bool ResetRotY1=false;
bool ResetRotY2=false;
bool ResetRotY3=false;

bool ResetRotX1=false;
bool ResetRotX2=false;
bool ResetRotX3=false;
bool stop=false;
int main()
{
    if (!glfwInit()) {
        printf("Could not initialize glfw.\n");
        return -1;
    }

    GLFWwindow* window;
    window = glfwCreateWindow(500, 720, "OpenGL TP 1", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }


    glfwSetScrollCallback(window, scroll_callback);
//    glfwSetMouseButtonCallback(window, mouse_button);
    glfwMakeContextCurrent(window);

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
     printf("Could not initialize GLAD\n");
     return -1;
    }
    glfwSetFramebufferSizeCallback(window, Resize);


	//**********************************//
	// vec3 normalVectorYellowFace = vec3(0.0f, -0.5f, 0.0f);
	// vec3 normalVectorRedFace = vec3(0.0f, 0.0f, 0.5f);
	// vec3 normalVectorBlueFace = vec3(0.5f, 0.0f, 0.0f);
	// vec3 normalVectorOrangeFace = vec3(0.0f, 0.0f, -0.5f);
	// vec3 normalVectorGreenFace = vec3(-0.5f, 0.0f, 0.0f);
	// vec3 normalVectorWhiteFace = vec3(0.0f, 0.5f, 0.0f);

	vec3 normalVectorRedFace = vec3(0.0f, 0.0f, 0.5f);
     STRVertex vertices[] = {
    {vec3(1.0f, -1.0f, 1.0f),  vec3(1.0f, 0.83f, 0.0f), vec2(1.0f, 1.0f), normalVectorRedFace},//YellowFace
    {vec3(1.0f, -1.0f, -1.0f), vec3(1.0f, 0.83f, 0.0f), vec2(1.0f, 0.0f), normalVectorRedFace},//
    {vec3(-1.0f, -1.0f, -1.0f), vec3(1.0f, 0.83f, 0.0f), vec2(0.0f, 0.0f), normalVectorRedFace},//
    {vec3(-1.0f, -1.0f, 1.0f), vec3(1.0f, 0.83f, 0.0f), vec2(0.0f, 1.0f), normalVectorRedFace},//

    {vec3(1.0f, -1.0f, 1.0f),  vec3(0.72f, 0.0f, 0.0f), vec2(1.0f, 0.0f), normalVectorRedFace},//RedFace4
    {vec3(1.0f, 1.0f, 1.0f),   vec3(0.72f, 0.0f, 0.0f), vec2(1.0f, 1.0f), normalVectorRedFace},//
    {vec3(-1.0f, 1.0f,1.0f),   vec3(0.72f, 0.0f, 0.0f), vec2(0.0f, 1.0f), normalVectorRedFace},//
    {vec3(-1.0f, -1.0f, 1.0f), vec3(0.72f, 0.0f, 0.0f), vec2(0.0f, 0.0f), normalVectorRedFace},//

    {vec3(1.0f, -1.0f, 1.0f),  vec3(0.0f, 0.27f, 0.68f), vec2(0.0f, 1.0f), normalVectorRedFace},//BlueFace8
    {vec3(1.0f, -1.0f, -1.0f), vec3(0.0f, 0.27f, 0.68f), vec2(0.0f, 0.0f), normalVectorRedFace},//
    {vec3(1.0f, 1.0f,-1.0f),   vec3(0.0f, 0.27f, 0.68f), vec2(1.0f, 0.0f), normalVectorRedFace},//
    {vec3(1.0f, 1.0f, 1.0f),   vec3(0.0f, 0.27f, 0.68f), vec2(1.0f, 1.0f), normalVectorRedFace},//

    {vec3(1.0f, -1.0f, -1.0f), vec3(1.0f, 0.35f, 0.0f), vec2(0.0f, 1.0f), normalVectorRedFace},//OrangeFace12
    {vec3(1.0f, 1.0f, -1.0f),  vec3(1.0f, 0.35f, 0.0f), vec2(1.0f, 1.0f), normalVectorRedFace},//
    {vec3(-1.0f, 1.0f,-1.0f),  vec3(1.0f, 0.35f, 0.0f), vec2(1.0f, 0.0f), normalVectorRedFace},//
    {vec3(-1.0f, -1.0f, -1.0f), vec3(1.0f, 0.35f, 0.0f), vec2(0.0f, 0.0f), normalVectorRedFace},//

    {vec3(-1.0f, -1.0f, 1.0f), vec3(0.0f, 0.6f, 0.28f), vec2(0.0f, 1.0f), normalVectorRedFace},//GreenFace16
    {vec3(-1.0f, 1.0f, 1.0f),  vec3(0.0f, 0.6f, 0.28f), vec2(1.0f, 1.0f), normalVectorRedFace},//
    {vec3(-1.0f, 1.0f,-1.0f),  vec3(0.0f, 0.6f, 0.28f), vec2(1.0f, 0.0f), normalVectorRedFace},//
    {vec3(-1.0f, -1.0f, -1.0f), vec3(0.0f, 0.6f, 0.28f), vec2(0.0f, 0.0f), normalVectorRedFace},//

	{vec3(1.0f, 1.0f, 1.0f),   vec3(0.1f, 0.1f, 0.1f), vec2(1.0f, 1.0f), normalVectorRedFace},//WhiteFace20
    {vec3(1.0f, 1.0f, -1.0f),  vec3(0.1f, 0.1f, 0.1f), vec2(1.0f, 0.0f), normalVectorRedFace},//
    {vec3(-1.0f, 1.0f,-1.0f),  vec3(0.1f, 0.1f, 0.1f), vec2(0.0f, 0.0f), normalVectorRedFace},//
    {vec3(-1.0f, 1.0f, 1.0f),  vec3(0.1f, 0.1f, 0.1f), vec2(0.0f, 1.0f), normalVectorRedFace}//
    };
	unsigned int vertex_index []={
	        0,1,2,
	        2,3,0,
	        4,5,6,
	        4,6,7,
	        8,9,10,
	        8,10,11,
	        12,13,14,
	        12,14,15,
	        16,17,18,
	        16,18,19,
	        20,21,22,
	        20,22,23

	};
//----g-------------------------------------//

    //multiple instances
    vec3 instancesPositions[]={
        vec3(2.2f, 2.2f,2.2f),//0
        vec3(0.0f, 2.2f,2.2f),
        vec3(-2.2f, 2.2f,2.2f),
        vec3(2.2f, 2.2f,0.0f),
        vec3(0.0f, 2.2f,0.0f),
        vec3(-2.2f, 2.2f,0.0f),
        vec3(2.2f, 2.2f,-2.2f),
        vec3(0.0f, 2.2f,-2.2f),
        vec3(-2.2f, 2.2f,-2.2f),//8
        //middle row
        vec3(2.2f, 0.0f,2.2f),//9
        vec3(0.0f, 0.0f,2.2f),
        vec3(-2.2f, 0.0f,2.2f),
        vec3(2.2f, 0.0f,0.0f),
        vec3(-2.2f, 0.0f,0.0f),
        vec3(2.2f, 0.0f,-2.2f),
        vec3(0.0f, 0.0f,-2.2f),
        vec3(-2.2f, 0.0f,-2.2f),//16
        //bottom row
        vec3(2.2f, -2.2f,2.2f),//17
        vec3(0.0f, -2.2f,2.2f),
        vec3(-2.2f, -2.2f,2.2f),
        vec3(2.2f, -2.2f,0.0f),
        vec3(0.0f, -2.2f,0.0f),
        vec3(-2.2f, -2.2f,0.0f),
        vec3(2.2f, -2.2f,-2.2f),
        vec3(0.0f, -2.2f,-2.2f),
        vec3(-2.2f, -2.2f,-2.2f),//25
    };
    vec3 YouWon[]={
        vec3(2.2f, 2.2f,2.2f),//0
        vec3(0.0f, 2.2f,2.2f),
        vec3(-2.2f, 2.2f,2.2f),
        vec3(2.2f, 2.2f,0.0f),
        vec3(0.0f, 2.2f,0.0f),
        vec3(-2.2f, 2.2f,0.0f),
        vec3(2.2f, 2.2f,-2.2f),
        vec3(0.0f, 2.2f,-2.2f),
        vec3(-2.2f, 2.2f,-2.2f),//8
        //middle row
        vec3(2.2f, 0.0f,2.2f),//9
        vec3(0.0f, 0.0f,2.2f),
        vec3(-2.2f, 0.0f,2.2f),
        vec3(2.2f, 0.0f,0.0f),
        vec3(-2.2f, 0.0f,0.0f),
        vec3(2.2f, 0.0f,-2.2f),
        vec3(0.0f, 0.0f,-2.2f),
        vec3(-2.2f, 0.0f,-2.2f),//16
        //bottom row
        vec3(2.2f, -2.2f,2.2f),//17
        vec3(0.0f, -2.2f,2.2f),
        vec3(-2.2f, -2.2f,2.2f),
        vec3(2.2f, -2.2f,0.0f),
        vec3(0.0f, -2.2f,0.0f),
        vec3(-2.2f, -2.2f,0.0f),
        vec3(2.2f, -2.2f,-2.2f),
        vec3(0.0f, -2.2f,-2.2f),
        vec3(-2.2f, -2.2f,-2.2f),//25
    };
    //Les buffers d’index
    GLuint RedVAO;
    GLuint RedVBO;

    GLuint RedVAO2;
    GLuint RedVBO2;

    glGenVertexArrays(1, &RedVAO);
    glBindVertexArray(RedVAO);

    glGenBuffers(1, &RedVBO);
    glBindBuffer(GL_ARRAY_BUFFER, RedVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint RedIBO; //create indexBuffer object to reuse the vertices of the triangles
    GLuint RedIBO2; //create indexBuffer object to reuse the vertices of the triangles
    glGenBuffers(1, &RedIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RedIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36*sizeof(unsigned int), vertex_index, GL_STATIC_DRAW);

    //---------------------------------------//
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(STRVertex) , (void*)offsetof(STRVertex,position) );
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(STRVertex) , (void*)offsetof(STRVertex,couleur) );
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(STRVertex) , (void*)offsetof(STRVertex,coords) );
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(STRVertex) , (void*)offsetof(STRVertex,normal) );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glClearColor(0.2f, 0.4f, 0.6f, 0.0f);

    GLuint ShaderProgram;

    ShaderProgram = LoadShaders("shader/SimpleVertexShader.vertexshader",
    "shader/SimpleFragmentShader.fragmentshader");
    glUseProgram(ShaderProgram);

    float x=0;
    float y=1;
    float f=0;
    float y1=20;
    bool reinitialiseRotation=true;
    bool decide=false;
    bool middle=true;
    bool middle2=true;
    bool top=true;
    bool bottom=true;
    bool right=true;
    bool left=true;
//    for (int i=0; i<27; i++){
//        ModelsArray[i]={i,mat4(1.0f)};
//    }
    for (int i=0; i<26; i++){
        Models[i] = translate(mat4(1.0f),instancesPositions[i]);
    }
//    saveInitialState = Models;
    copy(std::begin(Models), std::end(Models), std::begin(saveInitialState));

//    randomize Rubiks Cube
//    randomizeCube(instancesPositions);

    //lighting
    vec3 lightPos = vec3(0.0f, 0.0f, 8.0f);
    vec4 lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glUniform4f(glGetUniformLocation(ShaderProgram, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(ShaderProgram, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(glGetUniformLocation(ShaderProgram, "camPos"), cameraPos.x, cameraPos.y, cameraPos.z);

    //texturing
    int widthImg, heightImg, numColCh;
    unsigned char* bytes = stbi_load("textures/tex.png", &widthImg, &heightImg, &numColCh, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint tex0Uni = glGetUniformLocation(ShaderProgram, "tex0");
    glUniform1i(tex0Uni, 0);

    //normal map
    bytes = stbi_load("textures/normal.png", &widthImg, &heightImg, &numColCh, 0);
    GLuint normalMap;
    glGenTextures(1, &normalMap);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normalMap);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint tex1Uni = glGetUniformLocation(ShaderProgram, "tex1");
    glUniform1i(tex1Uni, 1);

    while (!glfwWindowShouldClose(window)){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normalMap);
//        mat4 Model = mat4(1.0f);
        x=Xpos;
        y=Ypos;

        glfwGetCursorPos (window, &Xpos, &Ypos );

        mat4 Projection = perspective(radians(fov), 3.0f / 4.0f, 0.1f, 100.0f);
        mat4 View = lookAt(cameraPos,cameraOrigin,cameraUp);

        mat4 MVP = Projection * View ;
        //On crée une variable uniforme MVP
        GLuint MatrixID = glGetUniformLocation(ShaderProgram, "MVP");


        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Rotate Whole Cube
        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS){

                reinitialiseRotation=false;
                middle=true;
                top=true;
                bottom=true;


                if( glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
                    fixedRotX=false;
                    diffX = x - Xpos;
                    rotationX=diffX;
                    if(LastRotated=="X"){
                        rotX+=diffX;
                    }else{
                        LastRotated="X";//RotationX(rotation on the Y axis)
                        rotationY=0;
                        rotY=0;
                        rotX=diffX;
                    }

                }else if( glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
                       fixedRotY=false;
                       diffY = Ypos -y;
                       rotationY=diffY;

                       if(LastRotated=="Y"){
                           rotY+=diffY;
                       }else{
                           LastRotated="Y";//RotationY(rotation on the X axis)
                           rotationX=0;
                           rotX=0;
                           rotY=diffY;
                       }

                }


        }else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) != GLFW_PRESS){
            float temp;
            float res;

            if(fixedRotX==false){

                temp=rotX;
                res=((rotX/90)-floor(rotX/90))*90;
                if(abs(res) > 45){
                    rotationX=90-res;
                    rotX=rotationX;
                }else if(abs(res) <= 45){
                        rotationX=-res;
                        rotX=rotationX;
                }
                std::cout <<temp  <<"  :X:  "<< rotX<<std::endl;
            }else{
                rotationX=0;
            }

            if(fixedRotY==false){
//                    std::cout <<rotationX  <<"  here  "<< rotationY<<std::endl;
                temp=rotY;
                res=((rotY/90)-floor(rotY/90))*90;
                if(abs(res) > 45){
                    rotationY=90-res;
                    rotY=rotationY;
                }else if(abs(res) <= 45){
                        rotationY=-res;
                        rotY=rotationY;
                }
                std::cout <<temp  <<"  :Y:  "<< rotY<<std::endl;
            }else{
                rotationY=0;
            }
            fixedRotY=true;
            fixedRotX=true;

        }
         //Rotate rows and column
        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){

              diffX = x - Xpos;
              rotRow+=diffX;
              diffY = Ypos - y;
              rotCol+=diffY;
              glfwGetWindowSize(window, &width, &height); //get the height and the width of the screen
              int mouseX=Xpos, mouseY=Ypos;//window Coord to OpenglCoordinates
              mouseX=mouseX-(width-1)/2;
              mouseY=mouseY-(height-1)/2;
              mouseY*=-1;
              mat4 invertedProjection = inverse(Projection);
              vec4 ViewCoords = invertedProjection * vec4(mouseX, mouseY, -1,1);

              if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS){
                fixedColRot=false;

                LastRowColRotated="col";
                if((decided && right) ||(!decided && ViewCoords.x<24.5f && ViewCoords.x>9.0f)){
                      rotationY2=0;
                      rotationY3=0;
                      if(middle2){
                        rotationY2=rotY2*-1;
                        ResetRotY2=true;
                      }
                      if(left){
                        rotationY3=rotY3*-1;
                        ResetRotY3=true;
                      }
                      decided=true;
                      middle2=false;
                      right=true;
                      left=false;
                      rotationY1=diffY;
                      rotY1+=rotationY1;
//                      std::cout << " Top Row :"<<rotationX1<<std::endl;

                }else if((decided && middle2) || (!decided && ViewCoords.x<7.5f && ViewCoords.x>-7.5f)){
                      rotationY1=0;
                      rotationY3=0;
                      if(right){
                        rotationY1=rotY1*-1;
                        ResetRotY1=true;
                      }
                      if(left){
                        rotationY3=rotY3*-1;
                        ResetRotY3=true;
                      }
                      decided=true;
                      middle2=true;
                      right=false;
                      left=false;
                      rotationY2=diffY;
                      rotY2+=rotationY2;
//                      std::cout << " Middle Row "<<rotationX2<<std::endl;

                }else if((decided && left) || (!decided && ViewCoords.x>-24.5f && ViewCoords.x<-9.0f)){
                      rotationY1=0;
                      rotationY2=0;
                      if(right){
                        rotationY1=rotY1*-1;
                        ResetRotY1=true;
                      }
                      if(middle2){
                        rotationY2=rotY2*-1;
                        ResetRotY2=true;
                      }
                      decided=true;
                      middle2=false;
                      right=false;
                      left=true;
                      rotationY3=diffY;
                      rotY3+=rotationY3;
//                      std::cout << " Bottom Row "<<rotationX3<<std::endl;

                }
             }else if(glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS){
                fixedRowRot=false;
                LastRowColRotated="row";
                if((decided && top) || (!decided && ViewCoords.y<24.5f && ViewCoords.y>9.0f)){
                      rotationX2=0;
                      rotationX3=0;
                      if(middle){
                        rotationX2=rotX2*-1;
                        ResetRotX2=true;
                      }
                      if(bottom){
                        rotationX3=rotX3*-1;
                        ResetRotX3=true;
                      }
                      decided=true;
                      middle=false;
                      top=true;
                      bottom=false;
                      rotationX1=diffX;
                      rotX1+=rotationX1;
//                      std::cout << " Top Row :"<<rotationX1<<std::endl;

                }else if((decided && middle) || (!decided && ViewCoords.y<7.5f && ViewCoords.y>-7.5f)){
                      rotationX1=0;
                      rotationX3=0;
                      if(top){
                        rotationX1=rotX1*-1;
                        ResetRotX1=true;
                      }
                      if(bottom){
                        rotationX3=rotX3*-1;
                        ResetRotX3=true;
                      }
                      decided=true;
                      middle=true;
                      top=false;
                      bottom=false;
                      rotationX2=diffX;
                      rotX2+=rotationX2;
//                      std::cout << " Middle Row "<<rotationX2<<std::endl;

                }else if((decided && bottom) || (!decided && ViewCoords.y>-24.5f && ViewCoords.y<-9.0f)){
                      rotationX2=0;
                      rotationX3=0;
                      if(middle){
                        rotationX2=rotX2*-1;
                        ResetRotX2=true;
                      }
                      if(top){
                        rotationX1=rotX1*-1;
                        ResetRotX1=true;
                      }
                      decided=true;
                      middle=false;
                      top=false;
                      bottom=true;
                      rotationX3=diffX;
                      rotX3+=rotationX3;
//                      std::cout << " Bottom Row "<<rotationX3<<std::endl;

                }
             }


        }else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS ){
            decided=false;
            float temp;
            float res;
            rotRow=0;
            rotCol=0;
            if(top){
                fixedRowRot=true;
                top=false;

                if(rotX1!=0){
                    temp=rotX1;
                    res=((rotX1/90)-floor(rotX1/90))*90;
                    if(abs(res) > 45){
                        rotationX1=90-res;
                        rotX1=rotationX1;
                    }else if(abs(res) <= 45){
                            rotationX1=-res;
                            rotX1=rotationX1;
                    }

                }
            }else{
               rotationX1=0;
            }

            if(middle){
                fixedRowRot=true;
                middle=false;
                if(rotX2!=0){
                    temp=rotX2;
                    res=((rotX2/90)-floor(rotX2/90))*90;
                    if(abs(res) > 45){
                        rotationX2=90-res;
                        rotX2=rotationX2;
                    }else if(abs(res) <= 45){
                            rotationX2=-res;
                            rotX2=rotationX2;
                    }
                }
            }else{
               rotationX2=0;
            }
            if(bottom){
                fixedRowRot=true;
                bottom=false;
                if(rotX3!=0){
                    temp=rotX3;
                    res=((rotX3/90)-floor(rotX3/90))*90;
                    if(abs(res) > 45){
                        rotationX3=90-res;
                        rotX3=rotationX3;
                    }else if(abs(res) <= 45){
                            rotationX3=-res;
                            rotX3=rotationX3;
                    }
                }
            }else{
               rotationX3=0;
            }

            //-----col rotation-----//

            if(right){
                fixedColRot=true;
                right=false;
                if(rotY1!=0){
                    temp=rotY1;
                    res=((rotY1/90)-floor(rotY1/90))*90;
                    if(abs(res) > 45){
                        rotationY1=90-res;
                        rotY1=rotationY1;
                    }else if(abs(res) <= 45){
                            rotationY1=-res;
                            rotY1=rotationY1;
                    }
                }
            }else{
               rotationY1=0;
            }
            if(middle2){
                fixedColRot=true;
                middle2=false;
                if(rotY2!=0){
                    temp=rotY2;
                    res=((rotY2/90)-floor(rotY2/90))*90;
                    if(abs(res) > 45){
                        rotationY2=90-res;
                        rotY2=rotationY2;
                    }else if(abs(res) <= 45){
                            rotationY2=-res;
                            rotY2=rotationY2;
                    }
                }
            }else{
               rotationY2=0;
            }
            if(left){
                fixedColRot=true;
                left=false;
                if(rotY3!=0){
                    temp=rotY3;
                    res=((rotY3/90)-floor(rotY3/90))*90;
                    if(abs(res) > 45){
                        rotationY3=90-res;
                        rotY3=rotationY3;
                    }else if(abs(res) <= 45){
                            rotationY3=-res;
                            rotY3=rotationY3;
                    }
                }
            }else{
               rotationY3=0;
            }
        }
        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) != GLFW_PRESS && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){

             if(canReset){
                Win=false;
                for (int i=0; i<26; i++){
                    Models[i]=translate(mat4(1.0f),instancesPositions[i]);
                }

                randomizeCube(instancesPositions);
                canReset=false;
             }
        }
        if(glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE){
            done=false;

            canReset=true;
        }
        mat4 MVPLoop;
        MVPLoop=MVP;
        int pos;//0: top / 1: middleRow / 2: bottom /3:right /4: middleCol /5:left
        for(unsigned int i=0; i<26;i++){
            MVPLoop=MVP;
            mat4 Model = mat4(1.0f);

            //create all instances
            Model = Models[i];
            vec4 position=Model[3];
            pos=6;//none
            if(LastRowColRotated=="row"){
                if(floor(position.y) >= 2){
                    pos=0;//top
                    std::cout << " Pos :"<<pos<<std::endl;
                }else if(floor(position.y) < 2 && floor(position.y) >-2){
                    pos=1;//middleRow
                    std::cout << " Pos :"<<pos<<std::endl;
                }else if(floor(position.y) <= -2){
                    pos=2;//bottom
                    std::cout << " Pos :"<<pos<<std::endl;
                }


            }else if(LastRowColRotated=="col"){
                if(floor(position.x) >= 2){
                    pos=3;//right
                    std::cout << " Pos :"<<pos<<std::endl;
                }else if(floor(position.x) < 2 && floor(position.x) >-2){
                    pos=4;//middleCol
                    std::cout << " Pos :"<<pos<<std::endl;
                }else if(floor(position.x) <= -2){
                    pos=5;//left
                    std::cout << " Pos :"<<pos<<std::endl;
                }
            }



            Model = translate(Model,vec3(instancesPositions[i][0]*-1,instancesPositions[i][1]*-1,instancesPositions[i][2]*-1));

            if(fixedRotX){//reset rotX if the rotation was fixed (means that the rotation has been rounded to a multiple of 90°)
                rotX=0;
            }
            if(fixedRotY){//reset rotX if the rotation was fixed (means that the rotation has been rounded to a multiple of 90°)
                rotY=0;
            }
            if(fixedRowRot){//reset rotX if the rotation was fixed (means that the rotation has been rounded to a multiple of 90°)
                rotX1=0;
                rotX2=0;
                rotX3=0;
            }
            if(fixedColRot){//reset rotX if the rotation was fixed (means that the rotation has been rounded to a multiple of 90°)
                rotY1=0;
                rotY2=0;
                rotY3=0;
            }

            Model = rotate(mat4(1.0f),radians(rotationX),vec3(0.0, 1.0, 0.0))*Model;
            Model = rotate(mat4(1.0f),radians(rotationY),vec3(1.0, 0.0, 0.0))*Model;

            if(pos == 0){
                //top
                Model = rotate(mat4(1.0f),radians(rotationX1),vec3(0.0, 1.0, 0.0))*Model;
            }else if(pos == 1){
                //middle
                Model = rotate(mat4(1.0f),radians(rotationX2),vec3(0.0, 1.0, 0.0))*Model;
            }else if(pos == 2){
                //bottom
                Model = rotate(mat4(1.0f),radians(rotationX3),vec3(0.0, 1.0, 0.0))*Model;
            }else if(pos == 3){
                //right
                Model = rotate(mat4(1.0f),radians(rotationY1),vec3(1.0, 0.0, 0.0))*Model;
            }else if(pos == 4){
                //middleCol

                Model = rotate(mat4(1.0f),radians(rotationY2),vec3(1.0, 0.0, 0.0))*Model;
            }else if(pos == 5 ){
                //left

                Model = rotate(mat4(1.0f),radians(rotationY3),vec3(1.0, 0.0, 0.0))*Model;
            }


            Model = translate(Model,vec3(instancesPositions[i][0],instancesPositions[i][1],instancesPositions[i][2]));
            glBindVertexArray(RedVAO);
//          save model
            Models[i]={Model};

            MVPLoop*=Model;
            glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "Model"), 1, GL_FALSE, &Model[0][0]);
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVPLoop[0][0]);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
        }
        //Check game state
        for(unsigned int i=0; i<26;i++){
            std::cout << " cord : "<<Models[i][3].z <<std::endl;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glDeleteTextures(1, &texture);
    glDeleteVertexArrays(1, &RedVAO);
    glDeleteBuffers(1, &RedVBO);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void scroll_callback(GLFWwindow *window,double xoffset, double yoffset){

    if(fov>= 20.0f && fov<=90.0f){
        fov-=yoffset;//scroll down => yoffset negative
    }else{
        if(fov<20.0f){
            fov=20.0f;
        }
        if(fov>90.0f){
            fov=90.0f;
        }
    }

}

int random(int min, int max) //range : [min, max]
{
   static bool first = true;
   if (first)
   {
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

void randomizeCube(vec3 instancesPositions[]){
    std::cout << " d: "<<std::endl;
   for (int j=0; j<1; j++){
        int num = random(0,12);
        int num2 = random(0,12);
        int ColRand = random(1,3);
        int RowRand = random(1,3);
        int rotCol = random(0,12);
        int rotRow = random(0,12);
        printf(" %d ", num);
        printf(" %d %d", rotCol,rotRow);

        //Global Rot
        for (int i=0; i<26; i++){
            Models[i] = translate(Models[i],vec3(instancesPositions[i][0]*-1,instancesPositions[i][1]*-1,instancesPositions[i][2]*-1));
            float r=90.0f*num;
            float r2=90.0f*num2;
            // Use current time as seed for random generator
//            srand(time(0));
            if(i>=0 && i<9){
                    //top
                Models[i] = rotate(mat4(1.0f),radians(r),vec3(0.0, 1.0, 0.0))*Models[i];
                Models[i] = rotate(mat4(1.0f),radians(r2),vec3(1.0, 0.0, 0.0))*Models[i];
            }

            if(i>=9 && i<17 ){
                //middle
                Models[i] = rotate(mat4(1.0f),radians(r),vec3(0.0, 1.0, 0.0))*Models[i];
                Models[i] = rotate(mat4(1.0f),radians(r2),vec3(1.0, 0.0, 0.0))*Models[i];
            }


            if(i>=17 && i<26 ){
                //bottom
                Models[i] = rotate(mat4(1.0f),radians(r),vec3(0.0, 1.0, 0.0))*Models[i];
                Models[i] = rotate(mat4(1.0f),radians(r2),vec3(1.0, 0.0, 0.0))*Models[i];
            }

            Models[i] = translate(Models[i],vec3(instancesPositions[i][0],instancesPositions[i][1],instancesPositions[i][2]));
//            Models[i] = rotate(mat4(1.0f),radians(rotationX1),vec3(0.0, 1.0, 0.0))*Models[i];
        }

        //Local Rot
        for (int i=0; i<26; i++){

            float r=90.0f*rotCol;
            float r2=90.0f*rotRow;
            mat4 Model = Models[i];
            vec4 position=Model[3];
            int test=6;//none
            Models[i] = translate(Models[i],vec3(instancesPositions[i][0]*-1,instancesPositions[i][1]*-1,instancesPositions[i][2]*-1));
            if(floor(position.y) >= 2){
                test=0;//top
//                std::cout << " test :"<<test<<std::endl;
            }else if(floor(position.y) < 2 && floor(position.y) >-2){
                test=1;//middleRow
//                std::cout << " test :"<<test<<std::endl;
            }else if(floor(position.y) <= -2){
                test=2;//bottom
//                std::cout << " test :"<<test<<std::endl;
            }else if(floor(position.x) >= 2){
                test=3;//right
//                std::cout << " test :"<<test<<std::endl;
            }else if(floor(position.x) < 2 && floor(position.x) >-2){
                test=4;//middleCol
//                std::cout << " test :"<<test<<std::endl;
            }else if(floor(position.x) <= -2){
                test=5;//left
//                std::cout << " test :"<<test<<std::endl;
            }

            if(test == 0 && RowRand==1){
                //top
                Models[i] = rotate(mat4(1.0f),radians(r),vec3(0.0, 1.0, 0.0))*Models[i];
            }else if(test == 1 && RowRand==2){
                //middle
                Models[i] = rotate(mat4(1.0f),radians(r),vec3(0.0, 1.0, 0.0))*Models[i];
            }else if(test == 2 && RowRand==3){
                //bottom
                Models[i] = rotate(mat4(1.0f),radians(r),vec3(0.0, 1.0, 0.0))*Models[i];
            }else if(test == 3 && ColRand==1){
                //right
                Models[i] = rotate(mat4(1.0f),radians(r2),vec3(1.0, 0.0, 0.0))*Models[i];
            }else if(test == 4 && ColRand==2){
                //middleCol
                Models[i] = rotate(mat4(1.0f),radians(r2),vec3(1.0, 0.0, 0.0))*Models[i];
            }else if(test == 5 && ColRand==3){
                //left
                Models[i] = rotate(mat4(1.0f),radians(r2),vec3(1.0, 0.0, 0.0))*Models[i];
            }


            Models[i] = translate(Models[i],vec3(instancesPositions[i][0],instancesPositions[i][1],instancesPositions[i][2]));
        }
}
}
