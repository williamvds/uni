# Universal Markup Language (UML)
> Universal Markup Language: a family of graphical notations that help in
> describing, designing, and organising object oriented software systems
- Latest version is 2.5 (June 2015)

- Pros
  - Ensures accuracy of communication, and enhances it
  - Captures logical software architecture independent of implementation
  - Helps in managing complexity
  - Enables reuse of design

## Use case specification
- Name
- Purpose
- Precondition(s)
- Base path (optimistic flow)
  - If everything goes desirably
- Alternative paths (pragmatic flows)
  - Every other possible way the system can be (ab)used
  - Including normal, alternative use, errors, and failures
- Postcondition(s)

## Use Case diagrams
- Behaviour diagrams that describe a __set of actions__ (use cases) that some 
    system or systems (the subject) should or can perform
  - May be in collaboration with with one ore more external users (actors)
- Do __not__ make any attempt to represent the __order or number of times__ that the
    systems actions and sub-actions should be executed

### Components
- Actors
  - Entities that interface with the system
  - Can be __people__ or __other systems__
  - Can be identified by considering the __roles__ they play

- Use cases
  - Based on __user stories__ (derived from discussions with stakeholders)
  - Represent what the actor wants the system to do
  - Only the name of the use case is represented in the diagram
    - Requires a use case specification in which each use case is formally
        described
    - Must be provided with a complete flow of activity (from actor's point of
        view)
    - Must be provide with observable and valuable results to the actor

- Relationships
  - Between use case and actor: Indicate which actors initiate which use cases
  - Between two use cases
    - Specify common functionality and simplifying use case flows
  - `<<include>>`
    - Multiple use cases share functionality - can be split into a shared use
        case
    - One use case can be required by another
    - The dependent use case re-uses the depended-on use case
  - `<<extends>>`
    - When activities might be performed as part of another, but not mandatory
        for use case to run successfully
    - When more capability is being added

- System boundary

## Activity diagram
- Graphical representations of workflows of step-by-step activities
- Includes actions related to individual use cases or across many use cases
- Supports parallel behaviour (unlike flowcharts)

### Components
- __Activities__: A state that is left once the activity is finished
- __Activity edge__: Transition that fires when previous activity completes
- __Synchronisation bar__
    - Thin filled rectangle
    - Brings together multiple parallel steps
- __Decisions__: Diamond shapes that represent decisions
- __Swim lanes__: A way to group activities performed by the same actor, or to 
    group activities in a single thread

## Sequence diagrams
- Temporal representation of objects and their interactions
- Shows objects and actors collaborating

- Horizontal axes: Which object/participant is acting
- Vertical axes: Represents time (vertically downwards meaning forward)

### Components
- __Participants__: Objects or actors that perform an action
- __Lifelines__: Lines that represent time as seen by the object
- __Messages__: Arrows that connect lifelines of sender and receiver
  - Represent events or the invocation of operations
- __Rectangle__: Represents when an object is alive
  - Covers an object's lifeline
  - Narrow in width
- __Creation arrow__: Represents a new object being created
  - 'New' is written above it
  - Ones after the start of a scenario appear lower than those created before
- __Deletion marker__: Represents an object being deleted
  - Marked by an X at the bottom of an object's lifeline
  - In some OOP languages this is handled automatically

## Class diagram
- Shows the existence of classes, their structures, and relationships
- Provides a logical view of the system

- Pros of the class model
  - Quickly and cheaply build a system to satisfaction of client
  - System is easy to maintain and adapt

- Classes include...
  - tangible things
  - roles
  - events
  - interactions

- Associations between classes...
  - correspond to verbs
  - exist if one class has to know about an object of another class, or vice 
      versa

> Multiplicity: The number of links between each instance of associated classes

### Components
- __Classes__: Their structure (properties), and behaviour (methods)
- __Relationships__
  - Association
  - Aggregation
  - Composition
  - Generalisation
  - Dependency
- Multiplicity and navigation indicators
  - __1__: exactly one
  - __*__: unlimited - zero or more
  - __0..*__: zero or more
  - __1..*__: one or more
  - __2..7__: specific range

### Representation
- Classes are depicted as rectangles with three compartments
  - Class name
  - __Attributes__: Data contained in an object of the class
  - __Operations__: Class behaviour

- Symbols
  - `+`: public
  - `#`: protected
  - `-`: private
  - `/`: derived
  - `$`: static

- __Association__: Bi-directional connection between two classes
  - The most general form of relationship
  - Solid line between two class rectangles
  - Text at either end of the line depict multiplicity

- __Aggregation__: _Is a part of_ relationship
  - Solid line with unfilled diamond (`◇`) at the end connecting to the class 
      that aggregates the other

- __Composition__: Implies the owner is explicitly responsible for creating and 
    deleting the parts
  - Strong form of aggregation
  - Solid line with a filled diamond (`◆`) at the end of the class that
      aggregates

- __Generalisation__: _Is-a_ relationship
  - Solid line with unfilled triangle (`△`) pointer connected to the superclass

- __Realisation / Implementation__: A class is implements an interface
  - Dashed line with unfilled triangle (`△`) pointer connected to the interface

- __Dependency__: When changes in the definition of one class may cause changes to
    the other
  - Unidirectional
  - Dashed line with caret (triangle without base) pointing towards depended-on
      class

## State Machine diagram
- Visualises the possible states of a system and the events/messages that cause
    transitions between those states
- Also shows the action(s) that result from a state change

### States
> State: A condition during the life of an object - when it satisfies some 
> condition, performs some action, or waits for an event

- __Start__: The initial state of an object when created - every diagram has 
    exactly one
- __Stop__: An end to the flow - a diagram can have multiple

### Representation
- __States__: Rounded boxes, with the name of the state within them
- __Events__: Arrows pointing between the states, labelled, eg with a method name
- __Guards__: Conditions in events that indicate it depends on specific values of 
    an object's
    attributes
  - Affect the behaviour of the state machine - transition can only occur when
      condition is true
  - Condition appended to event arrow label, wrapped in [square brackets]

# Coding tools

## Documentation
- XDoc tools, like [Javadoc](http://www.oracle.com/technetwork/articles/java/index-137868.html), allow creating special comments
- These comments store... 
  - class/method purposes
  - method parameters and their descriptions
  - values returned from methods
- Tools can generate HTML pages with an organised layout of information about 
    the codebase

### Javadoc example
- __Tags__: Used to provide specific information
  - `@param name description`: A method parameter
  - `@return description`: The value returned by the method
  - `@see className`: A reference to another class

```java
/**
 * Returns an Image object that can then be painted on the screen.
 * The url argument must specify an absolute {@link URL}. The name
 * argument is a specifier that is relative to the url argument.
 * <p>
 * This method always returns immediately, whether or not the
 * image exists. When this applet attempts to draw the image on
 * the screen, the data will be loaded. The graphics primitives
 * that draw the image will incrementally paint on the screen.
 *
 * @param  url  an absolute URL giving the base location of the image
 * @param  name the location of the image, relative to the url argument
 * @return      the image at the specified URL
 * @see         Image
 */
public Image getImage(URL url, String name) {
 try {
   return getImage(new URL(url, name));
 } catch (MalformedURLException e) {
   return null;
 }
}
```

## Build files
> Build files: Provide a set of instructions for how a project should be 
> compiled or built

- aka build scripts
- Larger projects, that may rely on external resources, may require custom 
    build scripts
  - Can build in dependencies, package files, run tests, deploy software, etc

- Pros
  - __Portable__: (Ideally) work on all platforms necessary
  - __Configurable__
  - __Script other external processes__:
    - Testing
    - Metrics
    - Deployment
  - Avoid manually performing confusing compile logic 
      (eg managing CLASSPATH for Java)
  - Ensures consistent compiles

### Java build systems
#### [Ant](https://ant.apache.org)
- From circa 2000
- By the Apache Software Foundation
- Uses XML
- Contains
  - One project
  - Targets (containing tasks)
  - Tasks: A piece of code that can be executed
- Reliable, simple set of tools
- Procedural, but uses XML
  - Not good for large projects

```ant
<project name="MyProject" default="dist" basedir=".">
  <description>
    simple example build file
  </description>
  <!-- set global properties for this build -->
  <property name="src" location="src"/>
  <property name="build" location="build"/>
  <property name="dist" location="dist"/>

  <target name="init">
    <!-- Create the time stamp -->
    <tstamp/>
    <!-- Create the build directory structure used by compile -->
    <mkdir dir="${build}"/>
  </target>

  <target name="compile" depends="init"
    description="compile the source">
    <!-- Compile the java code from ${src} into ${build} -->
    <javac srcdir="${src}" destdir="${build}"/>
  </target>

  <target name="dist" depends="compile"
    description="generate the distribution">
    <!-- Create the distribution directory -->
    <mkdir dir="${dist}/lib"/>

    <!-- Put everything in ${build} into the MyProject-${DSTAMP}.jar file -->
    <jar jarfile="${dist}/lib/MyProject-${DSTAMP}.jar" basedir="${build}"/>
  </target>

  <target name="clean"
    description="clean up">
    <!-- Delete the ${build} and ${dist} directory trees -->
    <delete dir="${build}"/>
    <delete dir="${dist}"/>
  </target>
</project>
```

#### [Maven](https://maven.apache.org)
- Released 2004
- Also by Apache
- Intended to improve upon Ant
- Also uses XML
- Has knowledge of source file locations

#### [Gradle](https://gradle.org)
- Released 2012
- Tried to take the best parts of Ant and Maven
- Uses domain-specific language over XML
- Declarative
- More cleanly accomplishes required tasks of a typical development project, 
    from compilation through testing and deployment
- Official build system for Android

## Unit testing
- Focuses on testing the building blocks of software
- In OO, objects and methods can be tested

- In development...
  - we can focus on small units
  - we can test components separately and in parallel
  - it makes it easier to locate errors

- During maintenance...
  - Provide a set of tests for regression testing
    - Check for errors after maintaining or fixing software

- Can use testing frames, eg JUnit for Java
- Test names should be descriptive
  - Help tracking down where they occurred, may hint what caused it
- Need to also consider...
  - integration testing
  - acceptance testing

### Testing considerations

#### Equivalence classes
- Testing data is split into sets, in each set the values should give an 
    equivalent result (in terms of behaviour)

- __Guidelines__
  1. If input value is a range, test once in range, twice outside (< and >)
  2. If input value is a small set where behaviour differs for each, multiple 
      tests are required (one for each, and one outside)
  3. If specific conditions are tested, provide failing and succeeding test for
      each condition

#### Boundary conditions
- Values around boundaries are usually important
- In ranges of numbers, need to consider just before, on, and just after the
    range
  - eg test on the edge of the boundaries, and floating values just above/below
      them

#### Special values
- For numbers, 0 is often a special case
- Times
- Dates

#### Logic (decision coverage)
- Programs/methods can take different procedural paths due to conditionals
- Need to test all possible paths
- eg both parts of an if/else statement

### Test Driven Development (TDD)
- Writing tests after code has been written can cause issues
  - Tests may be written for the code to pass
  - Testing is delayed until the end of a coding session
  - Refactoring becomes difficult until there are tests

> Test Driven Development: Tests are written first, which are derived from
> business requirements to meet the specification

- The minimum amount of code is written - enough to pass the tests
  - You aren't gonna need it principle (YAGNI) - functionality should not be
      added until deemed necessary

# Repository tools

## Collaborative challenges
- Need to coordinate and manage contributions in large software, involving a
    large number of people
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
  - Ideally provide different channels to separate topics - keeps related 
      discussion(s) together
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
  - _Working folder_: The state of your local directory, in which you can make
      changes to files
  - 🠳`git add`
  - _Staging area_: Where your selected changes are prepared
  - 🠳`git commit`
  - _Local repository_: Your local copy of the repository
  - 🠳`git push` 🠱`git fetch`
  - _Remote repository_: The central, remote, location where all code is stored
      and changes are logged

- Branches can be used to separate work on different issues
  - `git checkout {branch name}`
  - Avoids clashing with other features being worked on
  - Merge into master can be managed using pull/merge requests

- __Issues__
  - Need to ensure that commit messages are helpful
  - Need to ensure contributors keep their local repositories up to date to
      avoid conflicts

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
> Software entities (classes, modules, functions, etc.) should be open for
> extension, but closed for modification.

- Open for extension
  - Behaviour of a module can change
  - Can change as requirements or needs of application changes

- Closed for modification
  - The source code of a module is treated as private

- Enforces abstraction

### Liskov's Substitution
> Subtypes must be substitutable for their base types

- Methods that use references to base classes must be able to use objects of a
    derived classes without knowing their class
- Subclasses should not inherit from a parent that is not fully applicable
- Ensures inheritance is used properly
- Example
  - The `Bird` class contains method `Fly()`
  - King Fishers and Ostriches are both birds
  - But Ostriches are flightless
  - So Ostriches should inherit from a different class, eg `FlightlessBird`

### Interface Segregation
> Clients should not be forced to depend upon interfaces that they do not use

- Classes implementing an interface must implement all methods
- Large interfaces should be broken down
  - Ensures interfaces...
    - have one responsibility
    - are understandable
    - are reusable

### Dependency Inversion
> High-level modules should not depend on low-level modules; Both should depend
> on abstractions.
> Abstractions should not depend on details; Details should depend on
> abstractions.

- Reduces coupling between layers of code by adding abstractions
- Enforces that higher-level modules depend on abstractions rather than 
    lower-level modules

### Code reuse
- Favour object aggregation over class inheritance
- Class inheritance breaks encapsulation
  - Subclasses have access to (non-private) properties and methods
- Object aggregation depends upon objects interacting via interfaces - ensuring
    encapsulation

## Design patterns
> Design patterns: Reusable solutions to common problems

- The _pattern_ provides an abstract description of the design problem and how a
    general arrangement of element solves it
- A _design pattern_ identifies...
  - participating classes and instances
  - their roles
  - the distribution of responsibilities

- Useful to know just enough patterns to tackle most problems

### Contents
- __Name__: A succinct handle to describe the problem, its solutions, and
    consequences. Useful for discussion and documentation
- __Problem__: Describes when to apply the pattern, sometimes providing a list of
    conditions
- __Solution__: Describes the elements that make up the design and their
    relationships
- __Consequences__: Describes the results and trade-offs (time and space). Useful
    when evaluating design alternatives

### Organisation
- __Purpose__: Reflect what the pattern does
  - __Creational__: Related to the process of object creation
  - __Structural__: Deal with the composition of classes and objects
  - __Behavioural__: Characterise how classes/object interact and distribute
      responsibility

- __Scope__: Specifies whether pattern applies to classes or objects
  - __Class__: Deal with relationships between classes and sub-classes 
      (fixed at compile-time)
  - __Object__: Deal with object relationships (changeable at runtime)

### Examples

#### Adapter
> Adapter: A single class responsible for joining the functionalities of
> independent or incompatible interfaces

- __Class adapter__: Uses multiple inheritance
- __Object adapter__: Uses object composition

#### Factory
> Factory: Creating objects without exposing the creation logic to the client,
> and referring to the created object using a common interface

- Eg, an application with a number of _Shape_ subclasses
  - A `ShapeFactory` creates instances of `Circle` and `Rectangle` when 
      provided with the respective string describing such a shape
  - Created objects are returned as _Shape_

#### Observer
> Observer: Notifying dependent objects of changes, in a one-to-many
> relationship

- Observed subject...
  - Keeps a list of objects that implement the respective _Observer_ interface
  - Run a method on all observers when the tracked event occurs
      (eg a property is changed)

#### State pattern
> State pattern: A number of objects represent various states, a context 
> object's behaviour varies as its state object changes

#### Singleton
> Singleton: A class of which only a single instance can be created

- Reference to instance stored as a (private) property
- Has a (static) method `getInstance()` that returns the instance
  - Creates instance if it has not already created

#### Model View Controller (MVC)
> MVC: A pattern in which the components of a system are broken up into Model,
> View, and Controller

- __Model__: Manages the state of the system, including any and all data
- __View__: Allows a user to interact with the model
- __Controller__: Acts as the interface between the _model_ and _view_

- __Pros__
  - Separates GUI development from program model
