# Object-orientation
## SOLID design principles
- By [Uncle Bob](http://butunclebob.com/ArticleS.UncleBob.PrinciplesOfOod)
- Attempts to provide design principles for high-quality object-oriented design

### Single Responsibility
> A class should have one and only one responsibility

- Otherwise code becomes coupled
  - Changing one part of a class may require changing another part
- Classes with multiple responsibilities should be split up
  - Pros
    - Supports reuse
    - Supports minimising modifications 

> A method should have one and only one responsibility
- Methods with multiple responsibilities should be split up
  - Pros
    - Supports reuse
    - Supports minimising modifications 

### Open-closed
> Software entities (classes, modules, functions, etc.) should be open for extension, 
> but closed for modification.

- Open for extension
  - Behaviour of a module can change
  - Can change as requirements or needs of application changes

- Closed for modification
  - The source code of a module is treated as private

- Enforces abstraction

### Liskov's Substitution
> Subtypes must be substitutable for their base types

- Methods that use references to base classes must be able to use objects of a derived classes 
without knowing their class
- Subclasses should not inherit from a parent that is not fully applicable
- Ensures inheritance is used properly
- Example
  - The class _Bird_ contains method `Fly()`
  - King Fishers and Ostriches are both birds
  - But Ostriches are flightless
  - So Ostriches should inherit from a different class, eg _FlightlessBird_

### Interface Segregation
> Clients should not be forced to depend upon interfaces that they do not use

- Classes implementing an interface must implement all methods
- Large interfaces should be broken down
  - Ensures interfaces...
    - have one responsibility
    - are understandable
    - are reusable

### Dependency Inversion
> High-level modules should not depend on low-level modules. Both should depend on abstractions. 
> Abstractions should not depend on details. Details should depend on abstractions.

- Reduces coupling between layers of code by adding abstractions
- Enforces that higher-level modules depend on abstractions rather than lower-level modules

### Code reuse
- Favour object aggregation over class inheritance
- Class inheritance breaks encapsulation
  - Subclasses have access to (non-private) properties and methods
- Use object aggregation 
  - Which depends upon objects interacting via interfaces - ensuring encapsulation

## Design patterns
> Design patterns: Reusable solutions to common problems

- The _pattern_ provides an abstract description of the design problem and how a general arrangement
of element solves it
- A _design pattern_ identifies... 
  - participating classes and instances
  - their roles
  - the distribution of responsibilities

- Useful to know just enough patterns to tackle most problems

### Contents
- __Name__: A succinct handle to describe the problem, its solutions, and consequences. Useful for
discussion and documentation
- __Problem__: Describes when to apply the pattern, sometimes providing a list of conditions
- __Solution__: Describes the elements that make up the design and their relationships
- __Consequences__: Describes the results and trade-offs (time and space). Useful when evaluating
design alternatives

### Organisation
- __Purpose__: Reflect what the pattern does
  - __Creational__: Related to the process of object creation
  - __Structural__: Deal with the composition of classes and objects
  - __Behavioural__: Characterise how classes/object interact and distribute responsibility

- __Scope__: Specifies whether pattern applies to classes or objects
  - __Class__: Deal with relationships between classes and sub-classes (fixed at compile-time)
  - __Object__: Deal with object relationships (changeable at runtime)

### Examples
#### Adapter
> Adapter: A single class responsible for joining the functionalities of independent or 
> incompatible interfaces

- __Class adapter__: Uses multiple inheritance
- __Object adapter__: Uses object composition

#### Factory
> Factory: Creating objects without exposing the creation logic to the client, and referring to the 
> created object using a common interface

- Eg, an application with a number of _Shape_ subclasses
  - A _ShapeFactory_ creates instances of _Circle_ and _Rectangle_ when provided with the respective 
string describing such a shape
  - Created objects are returned as _Shape_

#### Observer
> Observer: Notifying dependent objects of changes, in a one-to-many relationship

- Observed subject...
  - Keeps a list of objects that implement the respective _Observer_ interface
  - Run a method on all observers when the tracked event occurs (eg a property is changed)

#### State pattern
> State pattern: A number of objects represent various states, a context object's behaviour varies
> as its state object changes

#### Singleton
> Singleton: A class of which only a single instance can be created

- Reference to instance stored as a (private) property
- Has a (static) method `getInstance()` that returns the instance
  - Creates instance if it has not already created

#### Model View Controller (MVC)
> MVC: A pattern in which the components of a system are broken up into Model, View, and Controller

- __Model__: Manages the state of the system, including any and all data
- __View__: Allows a user to interact with the model
- __Controller__: Acts as the interface between the _model_ and _view_
