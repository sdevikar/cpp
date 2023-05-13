# C++ Software Design by Klaus Iglberger

## 1. The Art Of Software Design

### Guideline 1

- Maintainability: The most important thing for project's success is not the latest C++ features but the structure of the code. The structure will determine how easy it is to change, extend, scale and test the code.
- Dependencies: The goal should be to minimize artificial (unexpected) dependencies
  - Software architecture: The goal of software architecture is to minimize the human resources required to build and maintain the required system.
  - Software design: Software design is the art of managing interdependencies between software components. It aims at minimizing artificial (technical) dependencies and introduces the necessary abstractions and compromises.
The two definitions above are very similar and have no clear boundary between them.
![Three levels of software development](images/three_levels_of_software_development.png)

#### Software design
This level deals with maintainability, changeability, extensibility, testability, and scalability. Software design primarily deals with the interaction of software entities. This is the level at which one would think about which design patterns to use, etc. 

#### Software architectureAarchitecture usually entails the big decisions, the aspects of your software that are among the hardest things to change in the future. This involves big decisions like whether to use microservices, client-server architecture, etc.
Similar to Software design patterns, they define and address the structure and interdependencies among software entities. In contrast to design patterns, though, they usually deal with the key players, the big entities of your software (e.g., modules and components instead of classes and functions).

#### Summary 

UNDERSTAND THE IMPORTANCE OF SOFTWARE DESIGN
- Treat software design as an essential part of writing software.
- Focus less on C++ language details and more on software design.
- Avoid unnecessary coupling and dependencies to make software more adaptable to frequent changes.
- Understand software design as the art of managing dependencies and abstractions.
- Consider the boundary between software design and software architecture as fluid.

### Guideline 2

## 2. The Art Of Building Abstractions
## 3. The Purpose Of Design Patterns
## 4. The Visitor Design Pattern
## 5. The Strategy And Command Design Patterns
## 6. The Adapter, Observer, And CRTP Design Patterns
## 7. The Bridge, Prototype, And External Polymorphism Design Patterns
## 8. The Type Erasure Design Pattern
## 9. The Decorator Design Pattern
## 10. The Singleton Pattern
## 11. The Last Guideline

