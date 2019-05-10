#include <iostream>

using namespace std;
//das Blatt
enum tipo_hoja
{
	REDONDA, ALARGADA
};

class Hoja
{
  private:
    // addPrototype() saves each registered prototype here
    static Hoja *_prototypes[10];
    static int _nextSlot; // for "find and clone"
  public:
    virtual void draw() = 0; //a implementarse en las subclases
    static Hoja *findAndClone(tipo_hoja);
  protected:
    virtual tipo_hoja returnType() = 0;
    virtual Hoja *clone() = 0;
    // As each subclass of Image is declared, it registers its prototype
    static void addPrototype(Hoja *hoja)
    {
        _prototypes[_nextSlot++] = hoja;
    }
};

Hoja *Hoja::_prototypes[];
int Hoja::_nextSlot;

// Client calls this public static member function when it needs an instance
// of an Image subclass
Hoja *Hoja::findAndClone(tipo_hoja type)
{
  for (int i = 0; i < _nextSlot; i++)
    if (_prototypes[i]->returnType() == type)
      return _prototypes[i]->clone();
  return NULL;
}

class Hoja_Redonda: public Hoja
{
  private:
    // Mechanism for initializing an Image subclass - this causes the
    // default ctor to be called, which registers the subclass's prototype
    static Hoja_Redonda _hojaRedonda;
    // This is only called when the private static data member is initiated
    Hoja_Redonda()
    {
        addPrototype(this);
    }
    // Nominal "state" per instance mechanism
    int _id;
    static int _count;

  public:
    tipo_hoja returnType()
    {
        return REDONDA;
    }
    void draw()
    {
        std::cout << "Hoja_Redonda::draw " << _id << std::endl;
    }
    // When clone() is called, call the one-argument ctor with a dummy arg
    Hoja *clone()
    {
        return new Hoja_Redonda(1);
    }
  protected:
    // This is only called from clone()
    Hoja_Redonda(int dummy)
    {
        _id = _count++;
    }

};

// Register the subclass's prototype
Hoja_Redonda Hoja_Redonda::_hojaRedonda;
// Initialize the "state" per instance mechanism
int Hoja_Redonda::_count = 1;

class Hoja_Alargada: public Hoja
{
  private:
    Hoja_Alargada()
    {
        addPrototype(this);
    }
    static Hoja_Alargada _hojaAlargada;
    int _id;
    static int _count;
  public:
    tipo_hoja returnType()
    {
        return ALARGADA; //devuelve el tipo de "enum"
    }
    void draw()
    {
        std::cout << "Hoja_Alargada::draw " << _id << std::endl;
    }
    Hoja *clone()
    {
        return new Hoja_Alargada(1);
    }
  protected:
    Hoja_Alargada(int dummy)
    {
        _id = _count++;
    }

};
// Register the subclass's prototype
Hoja_Alargada Hoja_Alargada::_hojaAlargada;
// Initialize the "state" per instance mechanism
int Hoja_Alargada::_count = 1;

		// Simulated stream of creation requests
		const int NUM_IMAGES = 8;
		tipo_hoja input[NUM_IMAGES] =
		{
		  REDONDA, REDONDA, REDONDA, ALARGADA, REDONDA, ALARGADA, ALARGADA, REDONDA
		};

int main()
{
  Hoja *my_hojas[NUM_IMAGES];

  // Given an image type, find the right prototype, and return a clone
  for (int i = 0; i < NUM_IMAGES; i++)
    my_hojas[i] = Hoja::findAndClone(input[i]);

  // Demonstrate that correct image objects have been cloned
  for (int i = 0; i < NUM_IMAGES; i++)
    my_hojas[i]->draw();

  // Free the dynamic memory
  for (int i = 0; i < NUM_IMAGES; i++)
    delete my_hojas[i];
}
