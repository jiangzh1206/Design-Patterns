> 《Design Patterns in Modern C++》

# Design Patterns 

设计模式，是一套被反复使用、多数人知晓的、经过分类编目的、代码设计经验的总结。使用设计模式是为了可重用代码、  
让代码更容易被他人理解、保证代码可靠性、程序的重用性。

## SOLID 设计原则
----

* Single Responsibility Principle (SRP)  
    单一职责。
* Open-Closed Principle (OCP)  
    对扩展开放，对修改关闭。

* Liskov Substitution Principle(LSP)  
    里氏替换原则: 如果接口接受父类型, 也可以接受子类型, 不需要任何修改子类应该可以替换任何基类能够出现的地方,  
    并且经过替换以后，代码还能正常工作。

* Interface Segregation Principle(ISP)  
    接口隔离原则: 接口拆分(单一)

* Dependency Inversion Principle(DIP)  
    依赖倒置原则: 高级模块不应该依赖于低级模块，两者都应该依赖于抽象，抽象不应该依赖于细节。细节应该依赖于抽象。  
    面向接口，降低耦合（一个对象应对其他对象保持最小的了解，迪米特法则（Law of Demeter）又叫作最少知识原则）

## Creational Patterns 创造型模式  
----

### [1.Builder](https://github.com/jiangzh1206/Design-Patterns/tree/master/Builder)
将一个复杂对象的构建与其表示相分离，使得同样的构建过程(稳定)可以创建不同的表示(变化)。 ——《设计模式》GoF  
Builder模式和AbstractFactory模式在功能上很相似，因为都是用来创建大的复杂的对象，它们的区别是：Builder模式强调的是一步步创建对象，并通过相同的创建过程可以获得不同的结果对象，一般来说Builder模式中对象不是直接返回的。而在AbstractFactory模式中对象是直接返回的，AbstractFactory模式强调的是为创建多个相互依赖的对象提供一个同一的接口
分步构建复杂对象，步骤需要稳定，复杂对象各部分变化。
### [2.Factories](https://github.com/jiangzh1206/Design-Patterns/tree/master/Factory)  
定义一个用于创建对象的接口，让子类决定实例化哪一个类。Factory Method使得一个类的实例化延迟（目的：解耦，手段：虚函数）到子类。 ——《设计模式》GoF  
* A class that knows how to create objects
* A function that, when called, creates an object  
工厂通常是一个单独的类，它知道如何构造对象  
工厂方法是用作创建对象的一种方法的类成员，它通常替换构造函数。  
抽象工厂提供特定接口，具体事项由子类具体工厂实现

### [3.Prototype](https://github.com/jiangzh1206/Design-Patterns/tree/master/Prototype)
使用原型实例指定创建对象的种类，然后通过拷贝这些原型来创建新的对象。 ——《设计模式》GoF  
一个模型对象，我们可以复制，定制这些复制，然后使用它们。原型模式的挑战实际上是复制部分，其他的都很简单。  
Prototype模式同样用于隔离对象的使用者和具体类型(易变类)之间的耦合关系，它同样要求这些“易变类”拥有稳定的接口。  
Prototype模式对于“如何创建易变类的实体对象“采用”原型克隆“的方法来做，它使得我们可以非常灵活地动态创建”拥有某些稳定接口“的新对象——所需工作仅仅是注册一个新类的对象(即原型)，然后在任何需要的地方Clone。
Prototype模式中的Clone方法可以利用某些框架中的序列化来实现深拷贝。

### [4.Singleton](https://github.com/jiangzh1206/Design-Patterns/tree/master/Singleton)
保证一个类仅有一个实例，并提供一个该实例的全局访问点。 ——《设计模式》GoF

## Structural Patterns 结构型模式
----
### [5.Adapter](https://github.com/jiangzh1206/Design-Patterns/tree/master/Adapter)
将一个类的接口转换成客户希望的另一个接口。Adapter模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。  

### [6.Bridge](https://github.com/jiangzh1206/Design-Patterns/tree/master/Bridge)
将抽象部分与实现部分分离，使它们都可以独立的变化  
在有多种可能会变化的情况下，用继承会造成类爆炸问题，扩展起来不灵活  
实现系统存在多个角色，每个角色都可能变化  

### [7.Composite](https://github.com/jiangzh1206/Design-Patterns/tree/master/Composite)
组合模式，是为了解决整体和部分的一致对待的问题而产生的，要求这个整体与部分有一致的操作或行为。部分和整体都继承与一个公共的抽象类，  
这样，外部使用它们时是一致的，不用管是整体还是部分，使用一个方法即可遍历整体中的所有的部分。就像一个树形结构一样。

### [8.Decorator（装饰者）](https://github.com/jiangzh1206/Design-Patterns/tree/master/Decorator)
动态（组合）地给一个对象增加一些额外的职责。就增加功能而言，Decorator模式比生成子类（继承）更为灵活（消除重复代码 & 减少子类个数）。 ——《设计模式》GoF  
装饰者模式，在不修改现在有接口和实现类的基础上实现功能或者状态的添加

### [9.Facade（门面/外观模式）](https://github.com/jiangzh1206/Design-Patterns/tree/master/Facade)
为子系统中的一组接口提供一个一致(稳定)的界面，Façade模式定义了一个高层接口，这个接口使得这一子系统更加容易使用(复用)。 ——《设计模式》GoF  

### [10.Flyweight（享元模式）](https://github.com/jiangzh1206/Design-Patterns/tree/master/Flyweight)
运行共享技术有效地支持大量细粒度的对象。 ——《设计模式》GoF  
通常，有大量非常相似的对象的情况下使用FlyWeights

### [11.Proxy](https://github.com/jiangzh1206/Design-Patterns/tree/master/Proxy)
为其他对象提供一种代理以控制(隔离，使用接口)对这对象的访问。 ——《设计模式》GoF
## Behavioral Patterns 行为型模式

### [12.Chain of Responsibility](https://github.com/jiangzh1206/Design-Patterns/tree/master/Chain%20of%20Responsibility)  
使多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。将这些对象连成一条链，并沿着这条链传递请求，直到有一个对象处理它为止。

### [13.Command](https://github.com/jiangzh1206/Design-Patterns/tree/master/Command)

### [14.Interpreter（解释器）](https://github.com/jiangzh1206/Design-Patterns/tree/master/Interpreter)  
Interpreter(解释器)模式是一种特殊的设计模式，它建立一个解释器（Interpreter），对于特定的计算机程序设计语言，用来解释预先定义的文法。尽量不要在重要模块中使用解释器模式，因为维护困难。在项目中，可以使用脚本语言来代替解释器模式。

### [15.Iterator](https://github.com/jiangzh1206/Design-Patterns/tree/master/Iterator)  


### [16.Mediator（中介者）](https://github.com/jiangzh1206/Design-Patterns/tree/master/Mediator)

### [17.Memento（备忘录）](https://github.com/jiangzh1206/Design-Patterns/tree/master/Memento)  
在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态。这样以后就可以将该对象恢复到原先保存的状态。 ——《设计模式》GoF

### [18.Null Object](https://github.com/jiangzh1206/Design-Patterns/tree/master/Null%20Object)  
Null Object模式主要是消除对null进行检查，并简化代码。

### [19.Observer](https://github.com/jiangzh1206/Design-Patterns/tree/master/Observer)  
定义对象间的一种一对多（变化）的依赖关系，以便当一个对象(Subject)的状态发生改变时，所有依赖于它的对象都得到通知并自动更新。

### [20.State](https://github.com/jiangzh1206/Design-Patterns/tree/master/State)
允许一个对象在其内部状态改变时改变它的行为。对象看起来似乎修改了它的类  
适用：  
1.一个对象的行为取决于它的状态，并且它必须在运行时刻根据状态改变它的行为；  
2.一个操作中含有庞大的多分支的条件语句，且这些分支依赖于该对象的状态。这个状态通常用一个或多个枚举常量表示。  
&emsp;通常有多个操作包含这一相同的条件结构。State模式将每一个条件分支放入一个独立的类中。这使得你可以根据对象  
&emsp;自身的情况将对象的状态作为一个对象，这一对象可以不依赖于其它对象而独立变化。  

如果系统中某个类的对象存在多种状态，不同状态下行为有差异，而且这些状态之间可以发生转换时使用状态模式；如果系统  
中某个类的某一行为存在多种实现方式，而且这些实现方式可以互换时使用策略模式。

### [21.Strategy](https://github.com/jiangzh1206/Design-Patterns/tree/master/Strategy)  
定义一系列算法，把它们一个个封装起来，并且使它们可互相替换（变化）。该模式使得算法可独立于使用它的客户程序(稳  
定)而变化（扩展，子类化）。  
策略设计模式允许定义算法的框架，然后使用组合对象提供缺少的实现细节。

### [22.Template Method](https://github.com/jiangzh1206/Design-Patterns/tree/master/Template%20Method)  
在父类中实现某个通用的流程，具体实现细节在各个特定的子类中实现。与策略Strategy类似，Strategy使用组合（静态、动态），  
Template Method使用继承。


### [23.Visitor](https://github.com/jiangzh1206/Design-Patterns/tree/master/Visitor)  
表示一个作用与某对象结构中的各元素的操作。使得可以在不改变(稳定)各元素的类的前提下定义(扩展) 作用于这些元素的新操作(变化)。  

1、对象结构中对象对应的类很少改变，但经常需要在此对象结构上定义新的操作。   
2、需要对一个对象结构中的对象进行很多不同的并且不相关的操作，而需要避免让这些操作"污染"这些对象的类，也不希望在增加新操作时修改这些类。  
侵入，反射  
典型实现：double dispatch，visitor中实现visit()，对象中实现accept()  
Cyclic Visitor: 基于重载，访问者和类层次需互相认识（知道类型），用于稳定的类层次结构中  
Acyclic Visitor: 基于RTTI，对于对象层次没有限制，对性能有影响  


### [24.Maybe Monad](https://github.com/jiangzh1206/Design-Patterns/tree/master/MaybeMonad)
表示将一个运算过程，通过函数拆解成互相连接的多个步骤。你只要提供下一步运算所需的函数，整个运算就会自动进行下去。