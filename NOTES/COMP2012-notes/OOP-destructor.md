# Destructor & Garbage Collection

A destructor is a member function that is invoked automatically when the object goes out of scope or is explicitly destroyed by a call to **`delete`**.

If you do not define a destructor, the compiler will **provide a default one**; for many classes this is sufficient.



```c++
// spec1_destructors.cpp
#include <string>

class String {
public:
   String( char *ch );  // Declare constructor
   ~String();           //  and destructor.
private:
   char    *_text;
   size_t  sizeOfText;
};

// Define the constructor.
String::String( char *ch ) {
   sizeOfText = strlen( ch ) + 1;

   // Dynamically allocate the correct amount of memory.
   _text = new char[ sizeOfText ];

   // If the allocation succeeds, copy the initialization string.
   if( _text )
      strcpy_s( _text, sizeOfText, ch );
}

// Define the destructor.
String::~String() {
   // Deallocate the memory that was previously reserved
   //  for this string.
   delete[] _text;
}

int main() {
   String str("The piper in the glen...");
}
```

## Declaring destructors

Destructors are functions with the same name as the class but preceded by a tilde (`~`)

**Several rules govern the declaration of destructors. Destructors:**

- Do not accept arguments.
- Do not return a value (or **`void`**).
- Cannot be declared as **`const`**, **`volatile`**, or **`static`**. However, they can be invoked for the destruction of objects declared as **`const`**, **`volatile`**, or **`static`**.
- Can be declared as **`virtual`**. Using virtual destructors, you can destroy objects without knowing their type — the correct destructor for the object is invoked using the virtual function mechanism. 

Some of the