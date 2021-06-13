
/*
ID - (Number: 1 - 100,000)
Job Title - (Text: 30)
Email Address - (Text: 50)
FirstName LastName - (Text: 30)
PIN - (Number: 000-00-000)
Phone Number - (Number: 0-000-000-0000)
*/

using namespace std;

#define PERSON_SIZE sizeof(Person)
#define RECORD(N) (PERSON_SIZE * N)

int convert_pin_n(std::string pin_s);

struct Person{
    int pin_n;
    char pin_s[12];
    char name[30];
    char email[50];
    char jobtitle[30];
    char phone[15];
    bool isEmpty();
    Person(){};
    Person(string _pin, string _name, string _email, string _jobtitle, string _phone);
};

struct PersonData{

    fstream myfile;
    long current;
    long file_size;
    long size;

    PersonData();
    ~PersonData();
    Person get_person_by_id(int id);
    Person get_person_by_pin(int pin_n, fstream &ppm);
    Person linear_search(int pin);
    int add_person(Person &p);
    void goto_first_person();
    bool next_person();
    Person get_current_person();
    void update_size();
};

// added typedef for indexed array of pairs
typedef pair<int,int> DualData;
// DualData is the pair of ints where it's ordered <record id, PIN>

// new functions declarations
void SortByPIN(DualData the_array[], int array_size);
// FIXME add write bin fx


