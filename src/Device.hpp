#pragma once

#include <string>

enum class Status {
  ENABLED,
  DISABLED,
  ERROR
};

class Device {
    private:
        static unsigned int uniq_id;
        unsigned int id;        
        std::string name;
        Status status;
    
    public:
        Device (const std::string& newName, Status newStatus);
        Device (const std::string& newName);
        unsigned int getId() const;          // makes NO sense to return the const reference -> instead a copy
        // void setId(unsigned int newId);   // user should not be able to modify it
        const std::string& getName() const;  // makes sense to return the const reference -> instead a copy
        void setName(const std::string& newName);  // makes sense to give a const reference to save for -> later a copy will be made
        Status getStatus() const;            // makes NO sense to return the const reference -> instead a copy
        void setStatus(Status newStatus);
        std::string getStringStatus() const;
};

/*
const std::string& getName() const;
│                 │         │
│                 │         └─ Device wird durch getName() nicht verändert
│                 │
│                 └─ Rückgabe ist eine Referenz, keine Kopie
│
└─ String darf über diese Referenz nicht verändert werden

Kleine triviale Typen wie Integer und kleine Enums werden üblicherweise by value 
zurückgegeben. Eine Referenz bringt hier typischerweise keinen Vorteil und koppelt die
Rückgabe unnötig an die Lifetime des Objekts

*/