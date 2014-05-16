#include "stdafx.h"
#include "glview.h"

#pragma region // --- OpenGL �ϐ� ---
const double MY_MINDISTANCE = 0.1;
const double MY_MAXDISTANCE = 10000.0;
const double CAMERA_DISTANCE = 30.0; //�J�����ƍ��W�n�̋���

int MouseX,MouseY;
int onMouseX,onMouseY;
bool M_left=false;
bool M_right=false;
bool M_middle=false;
bool M_wheel_up=false;
bool M_wheel_down=false;
bool phiState=true;
int wheel=0;
GLdouble upY = -1.0; //�J�����̌���[1.0��-1.0�ɂ���]

GLdouble fovy=30.0, onFovy=30.0, fovydif;
GLdouble eyeX, eyeY, eyeZ;
GLdouble eyeR, eyeTheta, eyePhi, onEyeTheta, onEyePhi, theta, phi;
int eyeXleft, eyeXright, eyeYup, eyeYdown, eyeZin, eyeZout;
GLdouble centerX=0, centerY=0, centerZ=0;
GLdouble onCenterX=0, onCenterY=0, onCenterZ=0;
GLdouble centerXdif, centerYdif, centerZdif;
int centerXleft, centerXright, centerYup, centerYdown;
#pragma endregion



#pragma region // --- Material ---
//////////////////////////////////////////
//ruby(���r�[)
MaterialStruct ms_ruby  = {
 {0.1745,   0.01175,  0.01175,   1.0},
 {0.61424,  0.04136,  0.04136,   1.0},
 {0.727811, 0.626959, 0.626959,  1.0},
 76.8};
//emerald(�G�������h)
MaterialStruct ms_emerald = {
  {0.0215,  0.1745,   0.0215,  1.0},
  {0.07568, 0.61424,  0.07568, 1.0},
  {0.633,   0.727811, 0.633,   1.0},
  76.8};
//jade(�Ő�)
MaterialStruct ms_jade = {
  {0.135,     0.2225,   0.1575,   1.0},
  {0.54,      0.89,     0.63,     1.0},
  {0.316228,  0.316228, 0.316228, 1.0},
  12.8};
//obsidian(���j��)
MaterialStruct ms_obsidian  = {
  {0.05375, 0.05,    0.06625, 1.0},
  {0.18275, 0.17,    0.22525, 1.0},
  {0.332741,0.328634,0.346435,1.0},
  38.4};
// pearl(�^��)
MaterialStruct ms_pearl  = {
  {0.25,     0.20725,  0.20725,  1.0},
  {1,        0.829,    0.829,    1.0},
  {0.296648, 0.296648, 0.296648, 1.0},
  10.24};
//turquoise(�g���R��)
MaterialStruct ms_turquoise  = {
  {0.1,     0.18725, 0.1745,  1.0},
  {0.396,   0.74151, 0.69102, 1.0},
  {0.297254,0.30829, 0.306678,1.0},
  12.8};
//brass(�^�J)
MaterialStruct ms_brass  = {
  {0.329412,  0.223529, 0.027451, 1.0},
  {0.780392,  0.568627, 0.113725, 1.0},
  {0.992157,  0.941176, 0.807843, 1.0},
  27.89743616};
//bronze(��)
MaterialStruct ms_bronze  = {
  {0.2125,   0.1275,   0.054,   1.0},
  {0.714,    0.4284,   0.18144, 1.0},
  {0.393548, 0.271906, 0.166721,1.0},
  25.6};
//chrome(�N���[��)
MaterialStruct ms_chrome  = {
  {0.25,    0.25,     0.25,     1.0},
  {0.4,     0.4,      0.4,      1.0},
  {0.774597,0.774597, 0.774597, 1.0},
  76.8};
//copper(��)
MaterialStruct ms_copper  = {
  {0.19125,  0.0735,   0.0225,  1.0},
  {0.7038,   0.27048,  0.0828,  1.0},
  {0.256777, 0.137622, 0.086014,1.0},
  12.8};
//gold(��)
MaterialStruct ms_gold  = {
  {0.24725,  0.1995,   0.0745,    1.0},
  {0.75164,  0.60648,  0.22648,   1.0},
  {0.628281, 0.555802, 0.366065,  1.0},
  51.2};
//silver(��)
MaterialStruct ms_silver  = {
  {0.19225,  0.19225,  0.19225, 1.0},
  {0.50754,  0.50754,  0.50754, 1.0},
  {0.508273, 0.508273, 0.508273,1.0},
  51.2};
//�v���X�`�b�N(��)
MaterialStruct ms_black_plastic  = {
  {0.0,    0.0,    0.0,  1.0},
  {0.01,   0.01,   0.01, 1.0},
  {0.50,   0.50,   0.50, 1.0},
  32};
//�v���X�`�b�N(�V�A��)
MaterialStruct ms_cyan_plastic  = {
  {0.0,   0.1,    0.06,    1.0},
  {0.0,       0.50980392,0.50980392,1.0},
  {0.50196078,0.50196078,0.50196078,1.0},
  32};
//�v���X�`�b�N(��)
MaterialStruct ms_green_plastic  = {
  {0.0,     0.0,   0.0,  1.0},
  {0.1,     0.35,  0.1,  1.0},
  {0.45,    0.55,  0.45, 1.0},
  32};
//�v���X�`�b�N(��)
MaterialStruct ms_red_plastic  = {
  {0.0,     0.0,     0.0,  1.0},
  {0.5,     0.0,     0.0,  1.0},
  {0.7,     0.6,     0.6,  1.0},
  32};
//�v���X�`�b�N(��)
MaterialStruct ms_white_plastic  = {
  {0.0,   0.0,     0.0,  1.0},
  {0.55,  0.55,    0.55, 1.0},
  {0.70,  0.70,    0.70, 1.0},
  32};
//�v���X�`�b�N(��)
MaterialStruct ms_yellow_plastic  = {
  {0.0,  0.0,     0.0,  1.0},
  {0.5,  0.5,     0.0,  1.0},
  {0.60, 0.60,    0.50, 1.0},
  32};
//�S��(��)
MaterialStruct ms_black_rubber  = {
  {0.02,   0.02,    0.02, 1.0},
  {0.01,   0.01,    0.01, 1.0},
  {0.4,    0.4,     0.4,  1.0},
  10.0};
//�S��(�V�A��)
MaterialStruct ms_cyan_rubber  = {
  {0.0,     0.05,    0.05, 1.0},
  {0.4,     0.5,     0.5,  1.0},
  {0.04,    0.7,     0.7,  1.0},
  10.0};
//�S��(��)
MaterialStruct ms_green_rubber  = {
  {0.0,    0.05,    0.0,  1.0},
  {0.4,    0.5,     0.4,  1.0},
  {0.04,   0.7,     0.04, 1.0},
  10.0};
//�S��(��)
MaterialStruct ms_red_rubber  = {
  {0.05,     0.0,     0.0,  1.0},
  {0.5,      0.4,     0.4,  1.0},
  {0.7,      0.04,    0.04, 1.0},
  10.0};
//�S��(��)
MaterialStruct ms_white_rubber  = {
  {0.05,   0.05,    0.05, 1.0},
  {0.5,    0.5,     0.5,  1.0},
  {0.7,    0.7,     0.7,  1.0},
  10.0};
//�S��(��)
MaterialStruct ms_yellow_rubber  = {
  {0.05,  0.05,    0.0,  1.0},
  {0.5,   0.5,     0.4,  1.0},
  {0.7,   0.7,     0.04, 1.0},
  10.0};
  
#pragma endregion

  
#pragma region // --- �`�ʊ֐� ---
/// /////////////////////////////////////////
///  �`�ʊ֐��@���̊֐����J��Ԃ����s�����
void disp(){
	
#pragma region // --- �}�E�X���� ---

	if(M_left && M_right){
	}else if(M_left){
		eyeTheta = (GLdouble)((MouseX - onMouseX)*velocity*2.0);
		eyePhi = (GLdouble)((MouseY - onMouseY)*velocity*2.0);
	}else if(M_middle){
		centerXdif = (GLdouble)((MouseX - onMouseX)*velocity);
		centerYdif = (GLdouble)((MouseY - onMouseY)*velocity);
	}else if(M_right){
		fovydif = (GLdouble)((MouseY - onMouseY)*velocity*20.0);
	}else{
		onCenterX = centerX;
		onCenterY = centerY;
		onCenterZ = centerZ;
		onEyeTheta = theta;
		onEyePhi = phi;
		onFovy = fovy;
		initParamMove();
		if(M_wheel_up==true){
			centerZdif = (GLdouble)velocity * 100;
			M_wheel_up = false;
		}else if(M_wheel_down==true){
			centerZdif = (-1.0) * (GLdouble)velocity * 100;
			M_wheel_down = false;
		}
	}

	fovy = onFovy + fovydif;
	
	theta = onEyeTheta+eyeTheta;
	phi = onEyePhi+eyePhi;
	
	if(phi>=M_PI*1.5){
		if(phiState==false){
			upY = -upY;
			phiState = true;
			onEyePhi = onEyePhi - M_PI*2.0;
			phi = onEyePhi+eyePhi;
		}
	}else if(phi>=M_PI*0.5){
		if(phiState==true){
			upY = -upY;
			phiState = false;
		}
	}else if(phi<=-M_PI*1.5){
		if(phiState==false){
			upY = -upY;
			phiState = true;
			onEyePhi = onEyePhi + M_PI*2.0;
			phi = onEyePhi+eyePhi;
		}
	}else if(phi<=-M_PI*0.5){
		if(phiState==true){
			upY = -upY;
			phiState = false;
		}
	}else if(phi>-M_PI*0.5 && phi<M_PI*0.5){
		if(phiState==false){
			upY = -upY;
			phiState = true;
		}
	}

	centerX = onCenterX - cos(theta)*centerXdif + sin(phi)*sin(theta)*centerYdif + cos(phi)*sin(theta)*centerZdif;
	centerY = onCenterY                       - cos(phi)*centerYdif           + sin(phi)*centerZdif;
	centerZ = onCenterZ + sin(theta)*centerXdif + sin(phi)*cos(theta)*centerYdif + cos(phi)*cos(theta)*centerZdif;

	eyeX = centerX - eyeR * sin(theta) * cos(phi);
	eyeY = centerY - eyeR * sin(phi);
	eyeZ = centerZ - eyeR * cos(theta) * cos(phi);

#pragma endregion

#pragma region // --- ���_���� ---
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, 1.0, MY_MINDISTANCE, MY_MAXDISTANCE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//�J�����̍��W, ���_, ���W�n�̌���
	gluLookAt(
		eyeX, eyeY, eyeZ,
		centerX, centerY, centerZ,
		0, upY, 0);
#pragma endregion

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	/// -----------���W���\��-------------
	glColor3d(1.0, 0.0, 0.0);
	drowCuboid(axisSize,axisThick,axisThick,axisSize/2., 0, 0,ms_jade,45.0,1.0,0.0,0.0);
	glColor3d(0.0, 1.0, 0.0);
	drowCuboid(axisThick,axisSize,axisThick, 0, axisSize/2.,0,ms_jade,45.0,0.0,1.0,0.0);
	glColor3d(0.0, 0.0, 1.0);
	drowCuboid(axisThick,axisThick,axisSize, 0, 0,axisSize/2.,ms_jade,45.0,0.0,0.0,1.0);
	
	/// ---------�����̕\��----------
	//glColor3d(1.0, 1.0, 1.0);
	
	for(int fileCount=0;fileCount<fileTotal;fileCount++)
	{
		glColor3d(1.0, 0.0+(GLdouble)fileCount/((GLdouble)fileTotal-1.0), 0.0);
		for(int i=0;i<rows;i++){
			
			GLdouble x = (GLdouble)allpoints[fileCount*rows*cols+i*cols+0];
			GLdouble y = (GLdouble)allpoints[fileCount*rows*cols+i*cols+1];
			GLdouble z = (GLdouble)allpoints[fileCount*rows*cols+i*cols+2];

			//�`��
			drowCuboid(cubeSize,cubeSize,cubeSize,x, y, z,ms_jade,angle,1.0,1.0,0.0);
		}
	}
	/*
	for(int i=0;i<data_rows;i++){
		//�F
		GLdouble x = (GLdouble)dataPoints.at<float>(i,0);
		GLdouble y = (GLdouble)dataPoints.at<float>(i,1);
		GLdouble z = (GLdouble)dataPoints.at<float>(i,2);
		//GLdouble d = - nearZ + z + x*sin(theta) + y*sin(phi);
		//glColor3d(1.0-d/farZ, 1.0-d/farZ, 1.0-d/farZ);
		glColor3d(1.0, 1.0, 1.0);
		//�`��
		drowCuboid(cubeSize,cubeSize,cubeSize,x, y, z,ms_jade,angle,1.0,1.0,0.0);
	}*/
	
	//glColor3d(1.0, 0.0, 0.0);
	//glutSolidTeapot(0.1);

	/*
	/// ----------������---------
	glColor3d(1.0, 1.0, 0.0);
	char str[256];
	sprintf(str, "%f", fovy);
    DrawString(str, window_w, window_h, 10, window_h - 70);
	sprintf(str, "x=%d", MouseX);
    DrawString(str, window_w, window_h, 10, window_h - 50);
	sprintf(str, "y=%d", MouseY);
    DrawString(str, window_w, window_h, 10, window_h - 30);
	*/

	glDisable(GL_LIGHTING);
	glFlush();
	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();
}
#pragma endregion


#pragma region // --- Initialize ---

void initParamMove(void){
	centerXdif = 0;
	centerYdif = 0;
	centerZdif = 0;
	eyeTheta = 0;
	eyePhi = 0;
	fovydif = 0;
}

void Initialize(){
	  //�����̐ݒ�--------------------------------------
	GLfloat lightPosition[4] = { 10.0, -10.0, -20.0, 0.0 }; //�����̈ʒu
	GLfloat lightDirection[3] = { 0.0, 0.0, 0.0}; //�����̕���
	GLfloat lightDiffuse[3]  = { 1.2,  1.2, 1.2  }; //�g�U��
	GLfloat lightAmbient[3]  = { 0.15, 0.15, 0.15 }; //����
	//GLfloat lightSpecular[3] = { 1.0,   1.0, 1.0  }; //���ʌ�

	
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	//��������
	//glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.01);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01);
}

void initFlag(void){
	eyeXleft=0;
	eyeXright=0;
	eyeYup=0;
	eyeYdown=0;
	centerXleft=0;
	centerXright=0;
	centerYup=0;
	centerYdown=0;
	eyeZin=0;
	eyeZout=0;
}

void initParam(void){
	centerX = 0;
	centerY = 0;
	centerZ = 0;
	onCenterX = 0;
	onCenterY = 0;
	onCenterZ = 0;
	centerXdif = 0;
	centerYdif = 0;
	centerZdif = 0;
	onEyeTheta = 0;
	eyeTheta = 0;
	onEyePhi = 0;
	eyePhi = 0;
	theta = 0;
	phi = 0;
	eyeR = 2;
	fovy = 30.0;
	onFovy = 30.0;
	fovydif = 0;
	upY = -1.0;
	phiState=true;
}
#pragma endregion


#pragma region // --- �}�E�X�ɂ�鎋�_���� ---
//�}�E�X(�N���b�N)
void mouse(int button, int state, int x, int y)
{
 if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
 {
  M_left=true;
  onMouseX = x;
  onMouseY = y;
 }else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
 {
  M_left=false;
 }
 if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
 {
  M_right=true;
  onMouseX = x;
  onMouseY = y;
 }else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
 {
  M_right=false;
 }
 if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
 {
  M_middle=true;
  onMouseX = x;
  onMouseY = y;
 }else if(button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
 {
  M_middle=false;
 }
}

//�h���b�O
void drag(int x, int y)
{
 MouseX=x;
 MouseY=y;
}

//�p�b�V�u
void passive(int x, int y)
{
 MouseX=x;
 MouseY=y;
}
//�z�C�[��
void MouseWheel(int wheel_number, int direction, int x, int y)
{
 if(direction==1){wheel++;M_wheel_up=true;}else{wheel--;M_wheel_down=true;}
}

#pragma endregion


#pragma region // --- �L�[�{�[�h�ɂ�鎋�_���� ---
/// /////////////////////////////////////////
///  �L�[�{�[�h�ɂ�鎋�_����
void glut_keyboard(unsigned char key, int x, int y){
	//�I��
	if(key=='q'){
		exit(0);
	}
	//���ɖ߂�
	if(key=='y'){
		initFlag();
		initParam();
	}
	//�_�Q�̃T�C�Y
	if(key=='0'){
		cubeSize += cubeSize_;
	}else if(key=='9'){
		cubeSize -= cubeSize_;
	}

	glutPostRedisplay();
}
#pragma endregion

void animate(void){
	glutPostRedisplay();
}

void myGlutIdle(){
	// ���̑����ĕ`��
	glutSetWindow(window1);
	glutPostRedisplay();
}


#pragma region // --- ������`�� ---
void DrawString(string str, int w, int h, int x0, int y0)
{
    glDisable(GL_LIGHTING);
    // ���s���e�ɂ���
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
 
    // ��ʏ�Ƀe�L�X�g�`��
    glRasterPos2f(x0, y0);
    int size = (int)str.size();
    for(int i = 0; i < size; ++i){
        char ic = str[i];
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18 , ic);
    }
 
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

#pragma endregion


#pragma region // --- ���̂̕`�� ---
/// //////////////////////////////////////////
/// ���̕`��
void drowSphere(double r, 
                double x, double y, double z, 
                MaterialStruct color){
	//��
	glPushMatrix();
      glMaterialfv(GL_FRONT, GL_AMBIENT, color.ambient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, color.diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, color.specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, &color.shininess);
    glTranslated( x, y, z);//���s�ړ��l�̐ݒ�
	glutSolidSphere(r, 3, 3);//�����F(���a, Z���܂��̕�����, Z���ɉ�����������)
	glPopMatrix();
}

/// //////////////////////////////////////////
/// ���\��ʑ̂̕`��
void drowDodecahedron(double r, 
                double x, double y, double z, 
                MaterialStruct color){
	//��
	glPushMatrix();
      glMaterialfv(GL_FRONT, GL_AMBIENT, color.ambient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, color.diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, color.specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, &color.shininess);
    glTranslated( x, y, z);//���s�ړ��l�̐ݒ�
	//
	//glutSolidDodecahedron(r);
	glPopMatrix();
}

/// //////////////////////////////////////////
/// �����̂̕`��
void drowCuboid(double a, double b, double c, 
                double x, double y, double z, 
                MaterialStruct color){

  GLdouble vertex[][3] = {
      { -a/2.0, -b/2.0, -c/2.0 },
      {  a/2.0, -b/2.0, -c/2.0 },
      {  a/2.0,  b/2.0, -c/2.0 },
      { -a/2.0,  b/2.0, -c/2.0 },
      { -a/2.0, -b/2.0,  c/2.0 },
      {  a/2.0, -b/2.0,  c/2.0 },
      {  a/2.0,  b/2.0,  c/2.0 },
      { -a/2.0,  b/2.0,  c/2.0 }
    };
  int face[][4] = {//�ʂ̒�`
      { 3, 2, 1, 0 },
      { 1, 2, 6, 5 },
      { 4, 5, 6, 7 },
      { 0, 4, 7, 3 },
      { 0, 1, 5, 4 },
      { 2, 3, 7, 6 }
    };
  GLdouble normal[][3] = {//�ʂ̖@���x�N�g��
    { 0.0, 0.0, -1.0 },
    { 1.0, 0.0, 0.0 },
    { 0.0, 0.0, 1.0 },
    {-1.0, 0.0, 0.0 },
    { 0.0,-1.0, 0.0 },
    { 0.0, 1.0, 0.0 }
  };
    glPushMatrix();
      glMaterialfv(GL_FRONT, GL_AMBIENT, color.ambient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, color.diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, color.specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, &color.shininess);
      glTranslated( x, y, z);//���s�ړ��l�̐ݒ�
      glBegin(GL_QUADS);
      for (int j = 0; j < 6; ++j) {
        glNormal3dv(normal[j]); //�@���x�N�g���̎w��
        for (int i = 0; i < 4; ++i) {
          glVertex3dv(vertex[face[j][i]]);
        }
      }
      glEnd();
    glPopMatrix();
}


/// //////////////////////////////////////////
/// ��]���l�����������̂̕`��
void drowCuboid(double a, double b, double c, 
                double x, double y, double z, 
                MaterialStruct color, 
                double theta, 
                double nx, double ny, double nz){
  double nn =sqrt(pow(nx,2)+pow(ny,2)+pow(nz,2));
  if(nn>0.0){
    nx = nx/nn;
    ny = ny/nn;
    nz = nz/nn;
  }
  glPushMatrix();
    glTranslated( x, y, z);//���s�ړ��l�̐ݒ�
    glPushMatrix();
      if(theta!=0 && nn>0.0) glRotated( theta , nx , ny, nz);
      drowCuboid(a, b, c, 0, 0, 0, color);
    glPopMatrix();
  glPopMatrix();
}

#pragma endregion