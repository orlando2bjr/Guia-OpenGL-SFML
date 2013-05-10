#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

// globais
// SFML //
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
sf::RenderWindow* pMainWindow;
sf::Event* pEventHandler;
sf::Font* pMainFont;
sf::Text* pMainText;
bool isRunning = true;
// OpenGL
struct AXIS3D
{
	double x_max; // margem esquerda
	double x_min; // margem direita
	double y_max; // base
	double y_min; // topo
	double z_max; // horizonte
	double z_min; // olho
	AXIS3D(double x_y_symmetrical, double z_symmetrical)
	{
		x_max = x_y_symmetrical;
		x_min = -x_y_symmetrical;
		y_max = x_y_symmetrical;
		y_min = -x_y_symmetrical;
		z_max = z_symmetrical;
		z_min = -z_symmetrical;
	}
	AXIS3D(double x_minimum, double x_maximum, double y_minimum, double y_maximum, double z_minimum, double z_maximum)
	{
		x_max = x_maximum;
		x_min = x_minimum;
		y_max = y_maximum;
		y_min = y_minimum;
		z_max = z_maximum;
		z_min = z_minimum;
	}

};
AXIS3D axis(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

// Laço Lúdico
void Setup(void);
void Input(void);
void Update(void);
void Render(void);
void Close(void);

int main(int argc, char* argv[])
{
	// Configuração
	Setup();

	// Laço Lúdico
	while (isRunning)
	{
		// Interações
		Input();
		// Atualizar dados lúdicos
		Update();
		// Exibir resultados
		Render();
	}

	Close();
	return 0;
}
void Setup(void)
{
	/* SFML */
	// Janela
	pMainWindow = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "OpenGLGame", sf::Style::Default, sf::ContextSettings(32));
	pMainWindow->setVerticalSyncEnabled(true);
	// Eventos
	pEventHandler = new sf::Event();
	// Fonte
	pMainFont = new sf::Font();
	if(!pMainFont->loadFromFile("../gothic.ttf"))
	{
		exit(0);
	}
	// Texto
	pMainText = new sf::Text();
	pMainText->setFont(*pMainFont);

	/* OpenGL */
	// Cor de limpeza dos pixels
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // preto transparente

	/* Frustrum */
	glOrtho(
		axis.x_min,	// X - margem esquerda
		axis.x_max,		// X - margem direita
		axis.y_min,		// Y - base
		axis.y_max,		// Y - topo
		axis.z_min,		// Z - olho
		axis.z_max		// Z - horizonte
		);
}

void Input(void)
{
	while (pMainWindow->pollEvent((*pEventHandler)))
	{
		if (pEventHandler->type == sf::Event::Closed)
		{
			// end the program
			pMainWindow->close();
			isRunning = false;
		}
		else if (pEventHandler->type == sf::Event::Resized)
		{
			// adjust the viewport when the window is resized
			glViewport(0, 0, pEventHandler->size.width, pEventHandler->size.height);
		}
	}

}

void Update(void)
{

}

void Render(void)
{
	/* OpenGL */
	// limpar buffers
	glClear(GL_COLOR_BUFFER_BIT);
	/* Desenhar */
	// Cor
	glColor3f(1.0f, 1.0f, 1.0f);
	GLfloat square_side = 0.5;
	// Polígono
	glBegin(GL_POLYGON);
		glVertex3f(0.25, 0.25, 0.0);
		glVertex3f(0.75, 0.25, 0.0);
		glVertex3f(0.75, 0.75, 0.0);
		glVertex3f(0.25, 0.75, 0.0);	
	glEnd();
	/* Gráficos da SFML  */
	pMainWindow->pushGLStates();				// salva estado da openGL
		pMainText->setString("Olá, Mundo!");
		pMainWindow->draw(*pMainText);			// recupera estado da openGL
	pMainWindow->popGLStates();
	pMainWindow->display();						// glFlush() + swapbuffers
}

void Close(void)
{
	delete pMainWindow;
	delete pEventHandler;
}
