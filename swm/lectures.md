# Repository tools
## Collaborative challenges
- Need to coordinate and manage contributions in large software, involving a large number of people
- Team members may be spread across several locations
- Large open-source projects may have a huge number of contributors
  - Linux kernel (2015)
    - 12,000 contributors
    - 20 million lines of code
    - Each release contains about 10,000 patches

- Need to...
  - maintain (other people's) code
  - manage the code in a distributed way
  - plan and coordinate tasks
  - plan changes and fixes

## Coordination
- __Kanban board__
  - Create tasks with specifications
  - Assign people to complete them
  - Organise tasks by progress
  - eg [Trello](https://trello.com), [GitHub projects](https://help.github.com/articles/about-project-boards), [GitLab issue boards](https://docs.gitlab.com/ee/user/project/issue_board.html)

- __Communication__
  - Provide a method for contributors to communicate with one another
  - Ideally provide different channels to separate topics - keeps related discussion(s) together
  - eg [Slack](https://slack.com), IRC

## Managing source code
- Use a source code version control or repository system
- eg Git, SVN (SubVersioN), CVS (Concurrent Versioning System)

- __Features__:
  - Store code centrally
  - Users check out versions, check in changes
  - Changes are logged, can be rolled back

### Using Git
- __Concepts__:
  - _Working folder_: The state of your local directory, in which you can make changes to files
  - 🠳`git add`
  - _Staging area_: Where your selected changes are prepared
  - 🠳`git commit`
  - _Local repository_: Your local copy of the repository
  - 🠳`git push` 🠱`git fetch`
  - _Remote repository_: The central, remote, location where all code is stored and changes are logged

- Branches can be used to separate work on different issues
  - `git checkout {branch name}`
  - Avoids clashing with other features being worked on
  - Merge into master can be managed using pull/merge requests
  
- __Issues__
  - Need to ensure that commit messages are helpful
  - Need to ensure contributors keep their local repositories up to date to avoid conflicts

## Continuous integration
- Regression testing is useful when maintaining code
- Ideally do very regular ( _continuous_ ) testing of all code
- Can use the central repository for this
- Testing can be completed over regular intervals or for every commit
  - Produces visible report of test results
  - Makes sure system is buildable (or compiles)
  - Lists code coverage (% lines tested)
  - Report coding style violations
  - Static analysis to find bugs
  - etc

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
