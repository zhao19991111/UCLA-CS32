//HW3
//medium.cpp



class Medium  //Medium Class
{
public:
	Medium(string id); //Constructor
	virtual ~Medium(); //Destructor
	string id() const;
	virtual string transmit(string message) const; //will be overidded by some functions
	virtual string connect() const = 0; //will always be overrided and never called
private:
	string m_id;  //private member m_id
};

class Phone : public Medium //phone inherits medium
{
public:
	Phone(string id, CallType type = TEXT); //Constructor
	~Phone(); ////override destructor
	virtual string transmit(string message) const; //override tranmit
	virtual string connect() const; //inherit connect
private:
	CallType m_type;  //private member m_type
};

class EmailAccount : public Medium //email account inherits medium
{
public:
	EmailAccount(string id, CallType type = TEXT); //Constructor
    ~EmailAccount(); //override destructor
	virtual string connect() const; //inherit connect
private:
	CallType m_type; //private member m_type
};

class TwitterAccount : public Medium //twitter account inherits medium
{
public: 
	TwitterAccount(string id, CallType type = TEXT); //Constructor
	~TwitterAccount(); //override destructor
	virtual string connect() const; //inherit connect
private:
	CallType m_type; //private member m_type
};

//implementations of constructors//

Medium::Medium(string id) 
	:m_id(id)
{}

Phone::Phone(string id, CallType type)
	:Medium(id), m_type(type)
{}

EmailAccount::EmailAccount(string id, CallType type)
	: Medium(id), m_type(type)
{}

TwitterAccount::TwitterAccount(string id, CallType type)
	: Medium(id), m_type(type)
{}

//implementation of id()//

string Medium::id() const
{
	return m_id;
}

//implementation of destructors//

Medium::~Medium() 
{}

Phone::~Phone()
{
	cout << "Destorying the phone " << id() << "."<<endl;
}

EmailAccount::~EmailAccount()
{
	cout << "Destorying the email account " << id() << "."<<endl;
}

TwitterAccount::~TwitterAccount()
{
	cout << "Destorying the Twitter account " << id() << "."<<endl;
}

//implementation of transmit//

string Medium::transmit(string message) const
{
	return "text: " + message;
}

string Phone::transmit(string message) const //overriding implementation of tranmit
{
	string call;
	if (m_type == VOICE) //discussion of message type
		call = "voice";
	else if (m_type == TEXT)
		call = "text";
	else
		call = "text"; //default message type
	return call + ": " + message;
}

//implementation of connect//

string Phone::connect() const
{
	return "Call";
}

string EmailAccount::connect() const
{
	return "Email";
}

string TwitterAccount::connect() const
{
	return "Tweet";
}







