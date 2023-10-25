#include <iostream>
#include <sys/types.h>


class IMemoryManager 
  {
  public:
    // following 2 functions need to be implemented in any class inheriting 
    virtual void* allocate(size_t) = 0; 
    virtual void   free(void*) = 0;
  };

// inheriting from IMemoryManager
class MemoryManager : public IMemoryManager
  {
    // A wrapper data structure meant to serve as our pointer when kept as part of the pool and as the complex object we are managing here
    struct FreeStore 
    {
      FreeStore* next;
    };
    void expandPoolSize ();
    void cleanUp();
    FreeStore* freeStoreHead;
    public:
      MemoryManager () {
        freeStoreHead = 0;
        expandPoolSize ();
      }
      virtual ~MemoryManager () {
        cleanUp ();
      }
      virtual void* allocate(size_t);
      virtual void free(void*);
  };

extern MemoryManager gMemoryManager; // Memory Manager, global variable

// complex class that we will use the demo memory manager
  class Complex 
  {
  public:
    Complex (double a, double b): r (a), c (b) {}
    inline void* operator new(size_t);
    inline void* operator delete(void*);
    private:
    union { 
      struct { 
        double r; // Real Part
        double c; // Complex Part
        };
      Complex * next;
    };
  };




// ---------- Overriding the New/Delete ----------//
void* operator new (size_t size) {
    return gMemoryManager.allocate(size);
};

void* operator new[ ] (size_t size) {
    return gMemoryManager.allocate(size);
}

void operator delete (void* pointerToDelete) {
    gMemoryManager.free(pointerToDelete);
} 


void operator delete[ ] (void* arrayToDelete) {
    gMemoryManager.free(arrayToDelete);
}

