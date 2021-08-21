## Chepter 2 --- built-in type
- **point out the type of literal val**
```C++
L'a'; //wchar_t
u8"hi"; //utf-8
42ULL; //unsigned long long
1E-3F; //float
3.14L //long double
```
- **declare a variable with extern and not init it**  
- **extern in C++**
- **constexpr 's define**
	1. *val is changeless*
	2. *inited when compile*
	3. *use on pointer,it is a top-level pointer*
---
- **auto**
	1. *ignore top-level const and keep low-level const,if the former is need,should point out directly*
	2. *reference top-level const will be kept*
- **decltype**  
---
- **const_cast**
```C++
const string &shorterString(const string &s1,const string &s2){
	return s1.size() <= s2.sise() ? s1 : s2;
}
string &shorterString(string &s1,string &s2){
	auto &r = shorterString(const_cast<const string&>(s1),const_cast<const string&>(s2));
	return const_cast<string&>(r);
}
```
---
- **overload and scope**  
	>The name we declared in the inner scope,will hide the same name in the outer scope
	>>In C++ ,name lookup is before the type checking
```C++
string read();
void print(const string&);
void print(double);
void fooBar(int ival){
	//hide the outer scope
	bool read = false;
	//err read is boolean type,not a function
	string s = read();
	//hide the print in the outer scope
	void print(int);
	//call above its head;
	print(ival);
	print(3.14);
}
```
---
- **function's default argument**
	1. *once a arg is set default argument ,then all the arg after it must be set.*
	2. *redeclare it can not change the default val has set,more args without default val could be set ,but follow the above rule.*
	3. *could not choose local variable to set the default argument's init val*
---
- **constexpr function**  
	1. *the return type and all the arguments type must be literal type*
	2. *In function body ,must exist only a return statement* 
	>constexpr function not permit to return the const expression  
	>>constexpr and inline functions are put in the head file
---
- **function match**
	1. *functions' name is the same as the called function's name*
	2. *the functions is visible in the call point*
	>best match: at least one more arg is matching better than other functions
---
- **function match and const arguments**
```C++
record lookup(Account&);
record lookup(const Account&);
const Account a;
Account b;

lookup(a);  //call const version
lookup(b);  //call normal version
```
---
- **function pointer**
```C++
bool lengthCompare(const string &,const string &);
bool (*pf)(const string &,const string &);  //uninitialized
pf = lengthCompare  //pf point to lengthCompare function
pf = &lengthCompare  //sign & is not forced

boo b1 = pf("hello","bye");  //call lengthCompare function
boo b1 = (*pf)("hello","bye");  //an equivalent call
pf = nullptr;
pf = 0;
string::size_type sumLength(const string&, const string&);
pf = sumLength;  //error, type not matched:return type not matched
bool cstringCompare(const char*,const char*);
pf = cstringCompare;  //error ,type not matched:arguments type not matched

//function pointer argument
void useBigger(const string &s1,const string &s2,bool pf(const string &,const string &));
void useBigger(const string &s1,const string &s2,bool (*pf)(const string &,const string &));

void useBigger(const string &s1,const string &s2,bool pf(const string &,const string &));
//something lost
typedef bool(*FuncP)(const string&,const string&);
typedef decltype(lengthCompare) *FuncP2;

auto f1(int) -> int (*)(int,int);
```
---
## Chepter 7 --- class  
---
- **default constructor**
	1. *if there is init val,then use it to initialize it*
	2. *else default to initialize the member*
	>if a constructor's arguments are all provided default val, that mean this class own the default constructor
	>>if this class include another class, default constructor work only when that class's default constructor works 
```C++
Sale_data() = default;  //do a request for generate default constructor
Sale_data()(const std::string &s): bookNo(s){}  //if the class include an const member, then it could be initialized only in this way
//understand the friend function declaration in class, it is only to point out the permission to access.
```
---
- **type member**  
	1. *it's also influenced by access level*
	2. *it must be defined first, then used, thus it defined at the begin of the class*
```C++
class Screen{
public:
	typedef std::string::size_type pos;  //or use using ... = ...
private:
......
};
```
---
- **class member**
	1. *the function defined inner the class is auto inline*
	2. *thus they should be put in the head file*
	3. *function member could be overloaded as well*
	>when we provide a class-inner init-val, must use {} or = to assign
---
- **class declaration**
```C++
class Screen;  //class declaration: forward declaration, before define it is incomplete type
//incomplete type can be used norrowly: Define pointer or ref point to the type , and declare funtion whose args and return type are this type are allowed.
```
- **delegating constructor**
```C++
class Sale_data {
public:
	Sale_data(string s,unsigned cnt, double price):bookNo(s),units_sold(cnt), revenue(cnt *price){}
	Sale_data(): Sale_data("", 0, 0){}
	Sale_data(string s): Sale_data(s, 0,0){}
	Sale_data(istream &istream &is): Sale_data(){ read(is,*this); }
};
```
---
- **implict converting constructor**
	1. *a constructor receive only one argument*
	2. *compiler only allow one step to convert type*
```C++
string null_book = "9999-999-99";
item.combine(null_book);  //string convert to Sale_data
item.combine("999-99-9");  //error, one step is allowed

//using explict to forbid convert type
//explict is only work on the constructor wiht only one argument
//use explict only in the class, repeat outside the class is not allowed
//explict constructor is only used to init directly
Sale_data item1(null_book);
Sale_data item2 = null_book  //error, copy form is forbade
```
---
- **static member**
	1. *static members exist outside any class*
	2. *static functions not include this-pointer, thus they couldn't be declared in const*
	3. *static members can be accessed by class scope sign directly*
	>static member can be used for default val and incomplete type
```C++
//static function member can be define in the class or outside the class.When in the case of later, the keyword 'static' are not allowd to repeat.
//for static data member, we must define and initialize every static data member
double Account::interestRate = initRate();
//we could provide an init val inner class for static data member only when it is const
class Account{
public:
	static double rate(){return interestRate; }
	static void rate(double);
private:
	static constexpr int period = 20;
	double daily_tbl[period];
};

class Screen{
public: 
	Screen& clear(char = bkground);
private:
	static Screen mem1;  //ok
	Screen *mem2;  //ok
	Screen mem3;  //err
	static const char bkground;
}
```
---
## Chepter 10 --- generic algorithm  
>Work on iterator, not depend on container type  
### Read only algorithm  
- **accumulate**  
```C++
//Val-Type val = accumulate(begin,end,Val-Type start-val  
//the third argument point out the return type and the type's plus sign
string num = accumulate(v.begin(),v.end(),"")  //err const char* has no operator sign for plus
//return the accumulated val
```
- **equal**
```C++
equal(r1.begin(),r1.end(),r2.begin());  
//equal function presume that the second sequence's length is the same as the first seq at least.
//if the element in the range is all equal then return true,or return false
```
---
### Write algorithm  
- **fill**
```C++
fill(vec.begin(),vec.end(),0);
//(b,e,t)
//b,e should be vaild or the res is undefine
fill_n(b,n,t)
```
- **copy**
```C++
//form:copy(src.b,src.e,dest) the third seqence should be able to contain the input element
//return the iterator point to the position after the last copyed val
copy(b,e,b2);
```
- **replace**
```C++
//replace(b,e,search_val,new_val);
//replace_copy(b,e,dest,search_val,new_val);
```
### Rearrangement algorithm
- **sort**
- **unique**
	>return the iterator point to the element afterthe last no-repeated element
```C++
void elimDups(vector<string> &word){
	sort(word.begin(),word.end());
	auto end_unique = unique(word.begin(),word.end());
	word.erase(end_unique,words.end());
}
```
---
### Predicate  
---
### Lambda expression
- **lambda**
	>[*capture list* ] (*parameter list* ) -> return type { *function body* }  
```C++
//lambda use the local variable always after caputure
//lambda can use the global variable directly
void func(vector<string> &word, vector<string>::size_type sz, ostream &os = cout, char c = ' '){
	for_each(word.begin(),word.end(),[&, c](const string &s) { os << s << c; });
	for_each(word.begin(),word.end(),[=,&os](const string &s) { os << s << c; });
}
/*if lambda function body include one more statement except return statement, 
then the compiler presume the return type as void*/
```
|capture form|explain|
|------|-----|
| [ ] | *empty capture list*|
| [names] | *the names are the local variable name*|
| [&] | *all local variable is captured by ref*|
|[=] | *all local variable is captured by val*|
|[&, identifier\_list]|*identifier_list variable is captured by val, sign & not allow placed before their each name*|
|[=, identifier\_list]|*identifier_list variable can not include **this**,sign & must be placed before their each name*|  

### Argument bind
- **bind**
	>auto *newCallable* = bind(*callable*, *arg_list* )   #include\<functional\>
```C++
using std::placeholders::_1;
bool check_size(const string &s,string::size_typr sz){
	return s.size() >= sz;
}
auto check6 = bind(check_size, _1, 6);
string s = "hello";
bool res = check6(s);  //equivalent call check_size(s,6)
auto g = bind(f,a,b,_2,c,_1);
g(_1, _2);  //equal to f(a,b,_2,c,_1)
//those argument not _n will be copyed ,we use std::ref to solve some problem 
for_each(word.begin(), word.end(), bind(print, ref(os), _1, ' '));
```
---
### Other iterator
- **insert iterator**  
	- back_inserter  
	- front_inserter  
	- inserter  

|operation|explain|
|-----|----|
|it = t|*call push_back or push_front or insert(t,p)*|
|*it,++it,it++|*do nothing on it*|
```C++
vector<int> vec;
fill_n(back_inserter(vec),10,0)
list<int> lst = {1,2,3,4};
list<int> lst2, lst3;
//4 3 2 1
copy(lst.begin(), lst.end(), front_inserter(lst2));
//1 2 3 4
copy(lst.begin(), lst.end(), inserter(lst3,lst.begin()));
```
---
- **stream iterator**
- **reverse iterator**
```C++
string line = "FIRST,MIDDLE,LAST";
auto comma = find(line.cbegin(),line.cend(),',');
cout<< string(line.cbegin(),comma) << endl;
auto rcomma = find(line.crbegin(),line.crend(),',');
//TSAL
cout<< string(line.crbegin(), rcomma) << endl;

/*
	     cbegin()    comma       rcomma.base() cend()
		^         ^               ^        ^
		F I R S T , M I D D L E , L A S T 
		                        ^       ^
				      rcomma  crbegin()
*/
```
- **move iterator**
---
### Chepter 11 --- Associative array
|type|explain|
|----|----|
|map|*key-value, the key is const*|
|set|*the key is the value, only keep one recording*|
|multimap|*key repeat is allowed*|
|multiset|*the same as above*|
|unordered_map|*Structed by hash function*|
|unordered_set|*the same as above*|
|unordered_multimap|...|
|unordered_multiset|...|
#### map

|for map and unordered_map|explain|
|----|---|
|c[k]|*return the key is k mapped value, if k is not in c, add k to c, and init it by value*|
|c.at(k)|*accese the key is k mapped value, if k is not in c, throw out a exception of out\_of\_range*|
```C++
map<string,size_t> word_count;
string word;
while (cin >> word)
	++word_count[word];
//if word is not in word_count, the above statement init it by value 0, and plus plus 1

```
- **pair**
	1. *the pair's constructor default to init the member by value*
	2. *the member is public*

|form|explain|
|-----|----|
|pair\<T1,T2> p|*p is a pair inited by value*|
|pair\<T1,T2> $p(v_1,v_2)$|*first is v1, second is v2*|
|pair\<T1,T2\>p = {$v_1,v_2$}<br>pair\<$T_1,T_2$\> p{$v_1,v_2$}|*the same as above*|
|make\_pair($v_1,v_2$)|*auto judge type*|
|p.first|....|
|p.second|...|
|p1 *relop* p2|*relationship operator sign defined as dictory-seqence*|
|p1 == p2|*only when first and second is each equal*|
|p1 != p2|...|


#### set 
```C++
bool compareIsbn(const Sale_data &lhs,const Sale_data &rhs){
	return lhs.isbn() < rhs.isbn();
}
multiset<Sale_data, decltype(compareIsbn)*> bookstore(compareIsbn);
```
#### associative array's operatings
- **add element**

|form|explain|
|---|---|
|key\_type|*the type of the key*|
|mapped\_type|*only use on map*|
|value\_type|*for set, it is the same as key type<br>for map, it is pair<const key_type, mapped_type>*|
|c.insert(v)<br>c.emplace(args)|*v type is value_type,args for constructing a element, return a pair, type is <iterator,bool>, for multi... insert always return the iterator point to the new element*|
|c.insert(b,e)<br>c.insert(il)|*b,e is a range of a container whose type is c::value_type, il is a initializer list*|
|c.insert(p,v)<br>c.emplace(p,args)|*p for a hint to insert*|

- **delete element**  

|form|explain|
|----|---|
|c.erase(k)|*delete key k, return a size_t val, to tell how many elements are deleted*|
|c.erase\(p\)|*delete a element given by a iterator, p must a true element, couldn't equal to c.end(), return a iterator point to the next, if p point to the last element, then return c.end()*|
|c.erase(b,e)|*delete the range of b to e,return e*|
- **accese element**

|form|explain|
|----|--|
|c.find(k)|*return a iterator point to the first k key value, if k is not in c, return c.end()*|
|c.count(k)|*return the number of key k mapped value, for unmuli-container, the return value is always 0 or 1*|
|c.lower\_bound(k)|*return a iterator point to the first key which is not less than k*|
|c.upper\_bound(k)|*return a iterator point to the first key which is greater than k*|
|c.equal\_range(k)|*return a iterator pair, to tell the range of key k, if k not exists, the two iterator all equal to c.end()*|

#### Unordered\_container

|form|explain|
|----|---|
|c.bucket\_count()|*the number of used bucket now*|
|c.max\_bucket\_count()|*the max size of the bucket held by this container*|
|c.bucket\_size(n)|*the number of the elements in the nth bucket*|
|c.bucket(k)|*key k is in which bucket?*|



### Chepter 12 --- Dynamic memory
#### shared_ptr  

|Usage|explain|
|----|---|
|make\_shared\<T\>(args)|*pass the args to a matched constructor to create it, and return pointer*|
|shared\_ptr\<T\>p(q)|*q can be a normol or a shared ptr*|
|p = q|*operator=(shareptr);*|
|p.unique()|*if p.use_count == 1, then return true*|
|p.use\_count()|*return the shareptr number,may slowly,mainly for debuging*|
|shared\_ptr\<T> p(u)|*p get the control of this pointer for unique\_ptr u, u reset to null*|
|shared\_ptr\<T> p(q,d)|*q can be normal or share ptr,the distinguish is that p use d to replace delete*|
|p.reset() p.reset(q) p.reset(q,d)|*q is a normol ptr*
- **new new[ ]**
```C++
string *ps = string(10,'9');
vector<int> *pv = new vector<int>{1,2,3,4,5};
//may be the same as share_ptr for init , try to prove it
auto p1 = new auto(obj);  //just one init val;
auto p2 = new auto{a,b,c};  //err just one init val can work by auto
//const
const int *pi = new const int (1024);
const string *ps = new const string;
//nothrow,bad_alloc
int *p1 = new int;
int *p2 = new (nothrow) int;
if(p2==nullptr)handle...
//new[n] n must be int, not enforced for constexpr
int *pia = new int[get_size()];
//new[n] return a pointer point to the first element
int *pia2 = new int[10]();//val inited
int *pia3 = new int[10]{0,1,23,4,5};  //if the provided num is less than the size, the rest val
//initialized, if more than, the new[] throw a bad_array_new_length exception
```
- **unique_ptr**
>only init by explict constructor ,no operator=().But you can return it when return from a function(std::move)  

|form|explain|
|-----|----|
|unique\_ptr\<T> u1<br>unique_ptr\<T,D> u2 |*D is atype of callable*|
|unique_ptr\<T,D> u(d)|*d is a funcptr , to replace delete*|
|u=nullptr|*delete what u points,put u on nullptr*|
|u.release()|*u give out the control, return ptr*|
|u.reset()<br>u.reset(q)<br>u.reset(nullptr)|understand on your own|
---
- **weak_ptr**  
>used together with shared_ptr

|form|explain|
|-----|----|
|weak\_ptr\<T> w<br>weak\_ptr\<T> w(sp)|*a empty weak_ptr<br>a sp --- shared_ptr*|
|w = p|*p could be a weak_ptr or shared_ptr*|
|w.reset()|*put w to empty*|
|w.use\_count|*shared_ptr num of w point*|
|w.expired()|*if w.use_count()==0,return true or false*|
|w.lock|*if w.expired() is true,return a empty shared_ptr or return a shared_ptr point to the same as w*|

- **unique\_ptr<T[ ]> u(new T[n])**
>this unique\_ptr point to the array not support the operator.() and operater->()  

|form|explain|
|---|---|
|unique\_ptr\<T[ ]> u|*u can point to a dynamic alloced array, element's type is T*|
|unique\_ptr\<T[ ]> u\(p\)|*u point to the normal ptr points to*|
|u[i]|*no explain*|
---
- **allocator**
>#include\<memory\> detach the memory alloc and construct

|form|explain|
|----|----|
|allocator\<T> a|*define a allocator class, which can malloc for the type T*|
|a.allocate(n)|*distrubute a original unconstructedmemory, could keep n of type T*|
|a.deallocate(p,n)|*give back the memory allocated by allocate, the p must be the returned ptr from allocate function, n is the arg when call allocate,before call this function, if the memory is constructed, you must call destroy function first, then call this function*|
|a.destroy\(p\)|*p is a ptr,type is T,to carry on the delete_function for what p points to, the pointed element must have been constructed, then this functon could be called*|
- **algorithm for allocator**  

|form|explain|
|---|---|
|uninitialized\_copy(b,e,b2)|*b2 is point to the uninitialized memory, the seqence of b2 must has enough space to contain the input, return the iterator after the last constructed element*|
|uninitialized\_copy\_n(b,n,b2)|*the same as above*|
|uninitialized\_fill(b,e,t)|*b is the uninitailized memory begin*|
|uninitialized\_fill\_n(b,n,t)|*the same as above*|

## Chepter 15 --- OOP
## Chepter 17 --- Special library device
- **tuple**

|   tuple's operatings|explain|
|----|-----|
|tuple\<T1,T2,$\cdots$,Tn> t|*All inited by value*|
|tuple\<T1,T2,$\cdots$,Tn> t(v1,<br>v2, $\cdots$, vn);|*this constructor is explict*|
|make\_tuple(v1,v2,..., vn)|*return a tuple init by the seqence*|
|t1 == t2<br>t1 != t2|*the same as other container*|
|t1 *relop* t2|*tuple use dictory seqence to compare t1 and t2 's elements, t1 and t2 must have the same number of elements*|
|get\<i>(t)|*return the reference of the element at pos i,if t is a lvalue then return lva-ref,if t is a rvalue the return rva-ref, all elements are public*|
|tuple\_size\<*tupleType*>::value|*a class template,could be initialized by a tuple, it has a member whose name is value whose type is **public constexpr static size_t**,express the number of the tuple has*|
|tuple\_element\<i,<br>tupleType>::type|*a class template,could be initialized by a int and tuple,it has a member whose name is type, to express the element's type gived in the tuple*|
```C++
tuple<size_t, size_t, size_t> threeD;  //all elements is inited by value 0
tuple<string, vector<double>, int, list<int>> someVal("constants",{3.14,2.718}, 42, {0,12,4,5,6});

tuple<size_t, size_t, size_t> threeD = {1,2,3};  //err, the constructor function is explicit
tuple<size_t, size_t, size_t> threeD{1,2,3};  //correct!
auto item = make_tuple("0-999-5454-X", 3, 20.00);  //auto judged <const char*, int, double>

//access the element
auto book = get<0>(item);  //start from 0
auto price = get<2>(item)/cnt;
get<2>(item) *= 0.8;

typedef decltype(item) trans;
size_t sz = tuple_size<trans>::value;  //return 3
tuple_element<1, trans>::type cnt = get<1>(item);  //cnt is a int

//only the two tuple has the same number of elements, then can be compared
tuple<string,string> duo("1","2");
tuple<size_t,size_t> twoD(1,2);
bool b = (duo == twoD);  //err couldn't compare string with size_t
tuple<size_t, size_t, size_t> threeD(1,2,3);
b = (twoD < threeD);  //err the number of the compared tuples are not the same.

//tuple has operator< and operator== ,we can pass it to algorithm
```
---
- **bitset**
>The ways to init

|form|explian|
|---- |---|
|bitset\<n\> b;|*b has n bit, every bit is init by value 0, this constructor is constexpr*|
|bitset\<n\> b(u);|*b is unsigned long long low n bit's copy, if n is beyond the bit of u, then the beyond part is set as 0*|
|bitset\<n\> b(s, <br>pos, m, zero, one);|*b is string s's copy from the pos,m char. s only can contain '0' or '1', if any else contained, the constructor throw a exception of invalid_argument. char is kept as <u>zero</u> and <u>one</u> . pos set 0 defaultly, m set as string::npos, zero set as '0', one set '1' defaultly.*|
|bitset\<n\> b(cp,pos,m,zero,one);|*the same as above, but cp point to a char-seq,if m is not provided,cp must point to a C-style char-seq, if m is provided, there should be at least m char from cp.*|
```C++
//when we use a int to init a bitset,this int type will convert to unsigned long long
//the size of bitset must be a constexpr
bitset<13> bitvec1(0xbeef);  //1111 0111 011111 the high bit is truncated
bitset<20> bitvec2(0xbeef);  //0000 1011 1110 1110 1111 the high bit is set 0
bitset<128> bitvec3(~0ULL);  //0~63 bit is set 1,63~127 is set 0

//initialized by a string
bitset<32> bitvec4("1100");  //2 3 bit is set 1,the rest of two bit are set 0, the high bits are set 0

string str("1111111000000011001101")  //1111 1110 0000 0011 0011 01
bitset<32> bitvec5(str,5,4); // 00000....0 1100
bitset<32> bitvec6(str, str.size()-4);  // 00000...0 1101
```
>The operatings of bitset

|form|explain|
|----|:---|
|b.any|*whether b has the set bit*|
|b.all|*whether all bits are set*|
|b.none|*whether b doesn't exist set bit*|
|b.count|*the set bits' number*|
|b.size|*return the bit number*|
|b.test(pos)|*if the pos bit is set, then return true or return false*|
|b.set(pos,v)<br>b.set()|*set the pos bit as the v, bool type, v default is true. if none arguments passed, set all bit*|
|b.reset(pos)<br>b.reset()|*set the pos bit unset or all bit unset*|
|b.flip(pos)<br>b.flip()|*change the pos bit or change all bit's status*|
|b[pos]|*access the pos bit, if b is const, then when b[pos] set return true, else return flase*|
|b.to\_long()<br>b.to\_ullong()|*return a unsigned long or unsigned long long which has the same bit as b. If b can't contain the bit, throw a overflow_error*|
b.to\_string(zero,one)|*return a string, to express the b. zero and one is default 0 and 1,to express the 0 and 1 in b*|
|os << b|*print b*|
|is >> b|*read from stdin, when the next char is not 1 or 0, or has reached the end of b.size(), read stop*|














