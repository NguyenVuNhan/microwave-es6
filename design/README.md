# Design Note

## Link to design (Lucidchart)
Link to the [design](https://app.lucidchart.com/invitations/accept/cd63f42a-2cf3-4476-bde3-46244447058b)


## Enbedded System Design

<div align="center">
    <img src="https://cdn.openlabpro.com/wp-content/uploads/2016/10/Embedded-system-block-diagram.png" />
	<br>
    <sup>An Embedded system – Block diagram</sub>
</div>

### Processor

### Interfaces

### Peripherals

## SOLID Principle
### S - Single-responsiblity principle
> A class should have one and only one reason to change, meanign that a class should have only one job

### O - Open-closed principle
> Object or entities should be open for extension but closed for modification

This simply means that a class should be easily extendable without modifying the class it self.

### L - Liskov substitution principle
> Let q(x) be a property provable about object sof x type T, THen q(y) should be provable for objects y of type Swhere S is a subtype of T.

All this is stating is that every suclass/derived class should be substitutable for their base/parent class.

### I - Interface segregation principle
> A client should never be forced to implement an interface that it doesn't use or clients shouldn't be forced to depend on methods they do not use

### D - Dependency Inversion Principle
> Entities must depend on abstractions not on concretion. It states that the high level module must not depend on the low level module, but they should depend on adstractions

