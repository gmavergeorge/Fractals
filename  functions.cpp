typedef void (*Function)(void); // function pointer type
typedef map<string, Function> func_map;

// ...

void some_function(void)
{
	cout << "asfdasfdqrwewr";
}
void age(void)
{
	cout << "afasdfasdfasdf";
}

// ...

func_map function;
functions.insert(std::make_pair("blah", &some_function));
functions.insert(std::make_pair("age", &age));

// ...

void call_script(const std::string& pFunction)
{
    func_map::const_iterator iter = m.find(pFunction);
    if (iter == m.end()){}

    (*iter->second)();
}