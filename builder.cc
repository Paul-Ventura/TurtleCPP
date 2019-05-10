#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

enum PersistenceType
{
  Tarjeta_de_video, Disco_duro, Procesador, Memoria_RAM
};

//La lista que contendrá las "partes" a utilizar en la construcción (el orden sí importa)
struct PersistenceAttribute
{
  PersistenceType type;
  char value[200];
};


/*
Abstract base class que declara el proceso de construccion estándard, la estructura del objeto
*/
class PC_Configuracion
{
  private:
    char _desc[200];
	char _temp[500];
  public:
    PC_Configuracion(char *type)
    {
        sprintf(_desc, "Configuracion para la maquina tipo: %s", type);
    }
    void setTarjetaVideo(char *f, char *v)
    {
        sprintf(_temp, "\n  Tarjeta_de_video(%s): %s", f, v);
        strcat(_desc, _temp);
    }
    void setDiscoDuro(char *q, char *v)
    {
        sprintf(_temp, "\n  Disco_duro(%s): %s", q, v);
        strcat(_desc, _temp);
    }
    void setProcesador(char *p, char *v)
    {
        sprintf(_temp, "\n  Procesador(%s): %s", p, v);
        strcat(_desc, _temp);
    }
    void setRAM(char *r, char *v)
    {
        sprintf(_temp, "\n  Memoria_RAM(%s): %s", r, v);
        strcat(_desc, _temp);
    }
    const char *getState()
    {
        return _desc;
    }

};

//Clase builder
class Builder
{
  protected:
    PC_Configuracion *_result;
  public:
    virtual void configurarTarjetaVideo(char*) = 0;
    virtual void configurarDiscoDuro(char*) = 0;
    virtual void configurarProcesador(char*) = 0;
	virtual void configurarRAM(char*) = 0;
    PC_Configuracion *getResult()
    {
        return _result;
    }

};

//Clase derivada concreta
class PC_Gamer: public Builder
{
  public:
    PC_Gamer()
    {
        _result = new PC_Configuracion("PC Gamer");
    }
    void configurarTarjetaVideo(char *name)
    {
        _result->setTarjetaVideo("8GB", name);
    }
    void configurarDiscoDuro(char *queue)
    {
        _result->setDiscoDuro("SSD 1TB", queue);
    }
    void configurarProcesador(char *type)
    {
        _result->setProcesador("Core i7", type);
    }
    void configurarRAM(char *ram)
    {
        _result->setRAM("32GB", ram);
    }
};

//Clase derivada concreta
class PC_Oficina: public Builder
{
  public:
    PC_Oficina()
    {
        _result = new PC_Configuracion("PC Oficina");
    }
    void configurarTarjetaVideo(char *name)
    {
        _result->setTarjetaVideo("2GB", name);
    }
    void configurarDiscoDuro(char *queue)
    {
        _result->setDiscoDuro("1TB", queue);
    }
    void configurarProcesador(char *type)
    {
        _result->setProcesador("Core i5", type);
    }
    void configurarRAM(char *ram)
    {
        _result->setRAM("16GB", ram);
    }
};

//Clase derivada concreta
class PC_Home: public Builder
{
  public:
    PC_Home()
    {
        _result = new PC_Configuracion("PC Home");
    }
    void configurarTarjetaVideo(char *name)
    {
        _result->setTarjetaVideo("2GB", name);
    }
    void configurarDiscoDuro(char *queue)
    {
        _result->setDiscoDuro("1TB", queue);
    }
    void configurarProcesador(char *type)
    {
        _result->setProcesador("Core i3", type);
    }
    void configurarRAM(char *ram)
    {
        _result->setRAM("8GB", ram);
    }
};


//Single reader object
class PC_Ensamblada
{
  private:
    Builder *_builder;
  public:
    void setBuilder(Builder *b)
    {
        _builder = b;
    }
    void construct(PersistenceAttribute[], int);

};


void PC_Ensamblada::construct(PersistenceAttribute list[], int num)
{
  for (int i = 0; i < num; i++)
    if (list[i].type == Tarjeta_de_video)
      _builder->configurarTarjetaVideo(list[i].value);
    else if (list[i].type == Disco_duro)
      _builder->configurarDiscoDuro(list[i].value);
    else if (list[i].type == Procesador)
      _builder->configurarProcesador(list[i].value);
    else if (list[i].type == Memoria_RAM)
      _builder->configurarRAM(list[i].value);
}

//Lista y el entero
const int NUM_ENTRIES = 4;

//Struct conteniendo el "type" y el "value"
PersistenceAttribute input[NUM_ENTRIES] = 
{
	{
		Tarjeta_de_video, ""
	}
	, 

	{
		Disco_duro, ""
	}
	, 

	{
		Procesador, ""
	}
	, 

	{
		Memoria_RAM, ""
	}
	

};

int main()
{
  PC_Gamer my_pc_gamer;										//Objeto del tipo PC_Gamer
  PC_Oficina my_pc_oficina;									//Objeto del tipo PC_Oficina
  PC_Home my_pc_home;										//Objeto del tipo PC_Home
  PC_Ensamblada my_pc_ensamblada;

  my_pc_ensamblada.setBuilder(&my_pc_gamer);				//Le pasamos un objeto PC_Gamer
  my_pc_ensamblada.construct(input, NUM_ENTRIES); 			//Se le pasa una lista y un entero
  cout << my_pc_gamer.getResult()->getState() << endl;

  my_pc_ensamblada.setBuilder(&my_pc_oficina);				//Le pasamos un objeto PC_Oficina
  my_pc_ensamblada.construct(input, NUM_ENTRIES);			//Se le pasa la misma lista y los mismos enteros
  cout << my_pc_oficina.getResult()->getState() << endl;

  my_pc_ensamblada.setBuilder(&my_pc_home);					//Le pasamos un objeto PC_Home
  my_pc_ensamblada.construct(input, NUM_ENTRIES);			//Se le pasa la misma lista y los mismos enteros
  cout << my_pc_home.getResult()->getState() << endl;

}
