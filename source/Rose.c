/*
 * 	Projekt Typu MEGC - Różyczka w OpenGL 
 * [Manipulator Elementów Graficznych w C]
 */
 
 /** 	COMMENTS ARE IN POLISH, THE CODE JUST HURTS THE EYES ... 	**/

// 1.07.2026 - I Could refactor and cleanup the code so it would be clearer, but that's a relic
// + no need to make it faster, it dosen't affect performance.
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GWM.h"
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <wchar.h>

#define PosX 100.0f
#define PosY 80.0f

WindowPosition WP =  {PosX, PosY};

GWMConfig GWM = {
	200.0f, 
	100.0f, 
	" Rose_GL\n Made By ApplehatDoesStuff\n\n MEGC Project #3", 
	PosX + 1.0f, 
	PosY + 78.0f
}; 

// Definicja struktury dla punktu
typedef struct {
    float x, y;
} Point;

// Punkty kontrolne - łodyga
Point lodyga_points[] = {
    {190, 80}, 
	{172, 120}, //średnia dwóch wymiarów
	{169, 173}
};

/* płaty Różyczki */
Point plat1_points[] = {
	{155, 174},
	{169, 170}, //średnia między 155 a 169
	{190, 177}
};

Point plat2_points[] = {
	{190, 177},
	{192, 187},
	{203, 197}
};

Point plat3_points[] = {
	{155, 174},
	{169, 190},
	{187, 199},  // 'zawyżka'
	{203, 197},
	{206, 197}
	
};

// łezka do płata 3-go
Point plat3_addon[] = {
	{206, 197},
	{212, 195},
	{212, 198},
	{203, 203}
};

Point plat4_point[] = {
	{155, 174},
	{153, 177},
	{153, 187},
	{150, 193}
};

Point plat5_points[] = {
	{147, 197},
	{140, 188},
	{157, 195},
	{164, 195},
	{175, 189}
};

Point plat5_addon[] = {
	{147, 197},
	{157, 197},
	{175, 189}
};

Point plat6_points[] = {
	{154, 195},
	{152, 200}
};

Point plat6_addon[] = {
	{155, 205},
	{153, 205},
	{150, 204},
	{145, 202},
	{148, 201},
	{153, 201},
	{157, 201},
	{159, 195}
};

Point plat7_points[] = {
	{156, 205},
	{152, 203},
	{157, 202},
	{165, 199},
	{170, 197},
	{185, 195},
	{193, 197},
	{198, 199},
};

Point plat8_points[] = {
	{160, 205},
	{155, 203},
	{160, 203},
	{163, 202},
	{167, 201},
	{174, 199},
	{179, 199},
	{197, 199},
	{200, 200},
	{202, 202}
};

Point plat9_points[] = {
	{184, 201},
	{186, 201},
	{190, 203},
	{195, 201},
	{200, 204},
	{204, 206},
	{205, 206},
	{199, 208},
	{185, 208},
	
};

Point plat10_points[] = {
	{165, 205},
	{170, 206},
	{174, 205},
	{183, 205}
};

Point plat11_points[] = {
	{170, 207},
	{178, 206},
	{183, 208}
};

Point plat12_points[] = {
	{172, 209},
	{178, 209}
};
// Funkcja obliczająca współczynniki Newtona (symbol Newtona)
int binomial_coefficient(int n, int k) {
    if (k > n - k) k = n - k;
    int result = 1;
    for (int i = 0; i < k; i++) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

// Funkcja obliczająca wartość funkcji bazowej Bernsteina
float bernstein_polynomial(int n, int i, float t) {
    return binomial_coefficient(n, i) * pow(t, i) * pow(1 - t, n - i);
}

// Funkcja obliczająca punkty krzywej Béziera
void bezier_curve(Point *pointctrl, int num_points, int segments, Point *result) {
    int n = num_points - 1;
    float dt = 1.0 / segments;
    for (int j = 0; j <= segments; j++) {
        float t = j * dt;
        float x = 0.0, y = 0.0;
        for (int i = 0; i <= n; i++) {
            float b = bernstein_polynomial(n, i, t);
            x += pointctrl[i].x * b;
            y += pointctrl[i].y * b;
        }
        result[j].x = x;
        result[j].y = y;
    }
}

/**** GŁÓWNY KOD ****/

int numlodyga_points = sizeof(lodyga_points) / sizeof(lodyga_points[0]);
int numplat1_points1 = sizeof(plat1_points) / sizeof(plat1_points[0]);
int numplat1_points2 = sizeof(plat2_points) / sizeof(plat2_points[0]);
int numplat1_points3 = sizeof(plat3_points) / sizeof(plat3_points[0]);
int numplat1_point3a = sizeof(plat3_addon) / sizeof(plat3_addon[0]);
int numplat2_points1 = sizeof(plat4_point) / sizeof(plat4_point[0]);
int numplat2_points2 = sizeof(plat5_points) / sizeof(plat5_points[0]);
int numplat2_point2a = sizeof(plat5_addon) / sizeof(plat5_addon[0]);
int numplat3_points1 = sizeof(plat6_points) / sizeof(plat6_points[0]);
int numplat3_point1a = sizeof(plat6_addon) / sizeof(plat6_addon[0]);
int numplat4_points1 = sizeof(plat7_points) / sizeof(plat7_points[0]);
int numplat5_points1 = sizeof(plat8_points) / sizeof(plat8_points[0]);
int numplat6_points1 = sizeof(plat9_points) / sizeof(plat9_points[0]);
int numplat7_points1 = sizeof(plat10_points) / sizeof(plat10_points[0]);
int numplat8_points1 = sizeof(plat11_points) / sizeof(plat11_points[0]);
int numplat9_points1 = sizeof(plat12_points) / sizeof(plat12_points[0]);
int segments = 100;

// Rysowanie krzywej kontrolnej
void KrzywaKontrolna(Point *pointctrl, int NUM_POINTS){
	glColor3f(0.9, 0.9, 0.9); // Jasnoszary kolor
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < NUM_POINTS; i++) {
        glVertex2f(pointctrl[i].x, pointctrl[i].y);
    }
    glEnd();
}

void PunktyKontrolne(Point *pointctrl, int NUM_POINTS){
	// Rysowanie punktów kontrolnych
    glColor3f(1.0, 010, 1.0); // Niebieski kolor
    glBegin(GL_POINTS);
    for (int i = 0; i < NUM_POINTS; i++) {
        glVertex2f(pointctrl[i].x, pointctrl[i].y);
    }
    glEnd();
}

// Rysowanie krzywej Béziera
void KrzywaBeziera(Point *pointctrl, int SEGMENTS, int NUM_POINTS){
	
	Point bezier_points[SEGMENTS + 1];
    bezier_curve(pointctrl, NUM_POINTS, SEGMENTS, bezier_points);
	
	glColor3f(1.0, 1.0, 1.0); // biały kolor
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= SEGMENTS; i++) {
        glVertex2f(bezier_points[i].x, bezier_points[i].y);
    }
    glEnd();
}

void DrawRose(){
		//łodyga
    KrzywaKontrolna(lodyga_points, numlodyga_points);
	PunktyKontrolne(lodyga_points, numlodyga_points);
	
    
	//fragment płatków
	
	//1 fragment
	KrzywaKontrolna(plat1_points, numplat1_points1);
	PunktyKontrolne(plat1_points, numplat1_points1);
	
	
	//2 fragment
	KrzywaKontrolna(plat2_points, numplat1_points2);
	PunktyKontrolne(plat2_points, numplat1_points2);
	
	
	//3 fragment
	KrzywaKontrolna(plat3_points, numplat1_points3);
	PunktyKontrolne(plat3_points, numplat1_points3);
	
    
    //dodatek do 3-go
	KrzywaKontrolna(plat3_addon, numplat1_point3a);
	PunktyKontrolne(plat3_addon, numplat1_point3a);
	
	
	// 2 płat - 1 fragment
	KrzywaKontrolna(plat4_point, numplat2_points1);
	PunktyKontrolne(plat4_point, numplat2_points1);
	
	
	// 2 płat - 2 fragment
	KrzywaKontrolna(plat5_points, numplat2_points2);
	PunktyKontrolne(plat5_points, numplat2_points2);
	

	// 2 płat - dodatek do 2-go
	KrzywaKontrolna(plat5_addon, numplat2_point2a);
	PunktyKontrolne(plat5_addon, numplat2_point2a);
	
	
	//3 płat - 1 fragment
	KrzywaKontrolna(plat6_points, numplat3_points1);
	PunktyKontrolne(plat6_points, numplat3_points1);
	
	
	//3 płat - 2 fragment
	KrzywaKontrolna(plat6_addon, numplat3_point1a);
	PunktyKontrolne(plat6_addon, numplat3_point1a);
	
	
	//4 płat
	KrzywaKontrolna(plat7_points, numplat4_points1);
	PunktyKontrolne(plat7_points, numplat4_points1);
	
	
	//5 płat
	KrzywaKontrolna(plat8_points, numplat5_points1);
	PunktyKontrolne(plat8_points, numplat5_points1);
	
	
	//6 płat
	KrzywaKontrolna(plat9_points, numplat6_points1);
	PunktyKontrolne(plat9_points, numplat6_points1);
	
	
	//7 płat
	KrzywaKontrolna(plat10_points, numplat7_points1);
	PunktyKontrolne(plat10_points, numplat7_points1);
	
	
	//8 płat
	KrzywaKontrolna(plat11_points, numplat8_points1);
	PunktyKontrolne(plat11_points, numplat8_points1);
	
	
	//9 płat ostatni!
	KrzywaKontrolna(plat12_points, numplat9_points1);
	PunktyKontrolne(plat12_points, numplat9_points1);
	
	
	KrzywaBeziera(lodyga_points, segments, numlodyga_points);
	KrzywaBeziera(plat1_points, segments, numplat1_points1);
	KrzywaBeziera(plat2_points, segments, numplat1_points2);
	KrzywaBeziera(plat3_points, segments, numplat1_points3);	
	KrzywaBeziera(plat3_addon, segments, numplat1_point3a);
	KrzywaBeziera(plat4_point, segments, numplat2_points1);	
	KrzywaBeziera(plat5_addon, segments, numplat2_point2a);	
	KrzywaBeziera(plat6_addon, segments, numplat3_point1a);	
	KrzywaBeziera(plat7_points, segments, numplat4_points1);
	KrzywaBeziera(plat8_points, segments, numplat5_points1);
	KrzywaBeziera(plat9_points, segments, numplat6_points1);
	KrzywaBeziera(plat10_points, segments, numplat7_points1);	
	KrzywaBeziera(plat11_points, segments, numplat8_points1);
	KrzywaBeziera(plat12_points, segments, numplat9_points1);
}

// Funkcja rysująca krzywą Béziera
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    DrawRose();
    glutSwapBuffers();
}

void Keyboard(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_F1:
            glClear(GL_COLOR_BUFFER_BIT);
            MakeWindow(&GWM, &WP);
            glutSwapBuffers();
            break;
    }
}

void keyboardN(unsigned char key, int x, int y) {
    if (key == 13) { // enter
        glClear(GL_COLOR_BUFFER_BIT);
        DrawRose();
        glutSwapBuffers();
    }
}


// Funkcja ustawiająca parametry okna
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Ustawienie koloru tła na biały
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 400, 0, 300); // Ustawienie układu współrzędnych
    glMatrixMode(GL_MODELVIEW);
}

// Funkcja główna
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Projekt MEGC #3 - Stworzony przez ApplehatDoesStuff");

    init();
    glutDisplayFunc(display);
	glutSpecialFunc(Keyboard);
	glutKeyboardFunc(keyboardN);
    glutMainLoop();
    return 0;
}
