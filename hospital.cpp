#include <iostream>

using namespace std;

// prima avevo implementato un bool come attributo di Patient, ora ho commentato questa cosa

class Patient{
    public:
        void setId(int id) { this->id = id; }
        void setName(string name) { this->name = name; }
        void setCondit(string cond) { this->condition = cond; }
        //void setPriority(bool p) { this->priority = p; }

        int getId() const { return id; }
        string getName() const { return name; }
        string getCondition() const { return condition; }
        //bool getPriority() const { return priority; }

        // c'e' anche l'operator<< per la classe Patient (vedi sotto)
        void stampa() const {

            cout << "Il paziente " << name << " ha ID = " << id 
            << ", la sua condizione e' " << condition << endl;

            /*
            if(priority == true)    cout << "Il paziente e' priority" << endl;
            else    cout << "Il paziente non ha priorita'" << endl;
            */

        }

        Patient(const int& i, const string& n, const string& c) : id(i), name(n), condition(c) {}
        // ho cancellato il costruttore che tiene conto dell'attributo priority
        Patient() : Patient(12345, "Puccini", "Gastroenterite") {}

        friend 
        ostream& operator<< (ostream& flusso, const Patient& p){

            flusso << "Id: " << p.getId() << ";\t Nome: " << p.getName() << ";\tCondizione: " << p.getCondition() << endl;

            //if( p.getPriority() == true ) flusso << "Il paziente e' prioritario.";
            return flusso;
        }

    private:
        int id;
        string name;
        string condition;
        //bool priority = false; // false di default
};

template <typename T>
struct Node{
    T data;
    Node<T> * next;
    Node<T> * prev;

};

template <typename T>
class Queue{
    public:

        bool isEmpty() const {
            if(head == NULL) return true;

            return false;
        }

        void enQueue(T key){

            Node<T> * newNode = new Node<T>;
            newNode->data = key;

            // Se metto head == tail potrebbe essere sia vuota, che un solo nodo. Allora meglio scrivere:
            if( isEmpty() == true ){
                cout << "la coda e' vuota" << endl;

                head = newNode;
                tail = newNode;

                newNode->next = NULL;
                newNode->prev = NULL;

                return;
            }
            
            cout << "La coda non e' vuota" << endl;

            newNode->prev = tail;
            newNode->next = NULL;
            tail->next = newNode;
            tail = newNode;

        }

        void deQueue(T key){

            if( isEmpty() == true ) return;

            Node<T> * tmp = head;

            (head->next)->prev = NULL;
            head = tmp->next;

            delete tmp;

        }

        void enQueuePriority(T key){
            
            if( isEmpty() == true ) { // inserisce direttamente

                cout << "Priority $$$ stiamo inserendo in testa con l'enqueue priority " << endl;
                enQueue(key);
                return;

            }
            cout << "PROVIAMO UN PO' :)" << endl;
            
            Node<T> * newNode = new Node<T>;
            newNode->data = key;

            Node<T> * curr = tail;
            int i = 0;

            
            while( (curr != NULL) && (i < 3) ){
                cout << "siamo dentro il while dell'enQueuePriority()" << endl;
                curr = curr->prev;
                i++;
            }

            if( curr == NULL ){ // vuol dire che inseriamo in head

                cout << "Priority $$$ ci sono meno di 4 nodi, allora inseriamo in testa" << endl;
                newNode->prev = NULL;
                head->prev = newNode;
                newNode->next = head;
                head = newNode;

                return;
            }
            
            cout << "Priority in mezzo $$$ a questo punto curr sarebbe l'ant del nostro nodo priority" << endl;
            newNode->prev = curr;
            newNode->next = curr->next;
            (curr->next)->prev = newNode;
            curr->next = newNode;
            
        }

        template <typename U>
	    friend ostream& operator<<(ostream& flusso_dati, const Queue<U>& q);


    public:
        Node<T> * head;
        Node<T> * tail;
};

template <typename U>
ostream& operator<< (ostream& flusso_dati, const Queue<U>& q){
    /*if(q.isEmpty() == true){
        //flusso_dati << "La lista e' vuota" << endl;
        return flusso_dati;
    }*/

    Node<U> * tmp = q.head;

    flusso_dati << "Head" << endl;
    // attenzione che se non ho implementato l'operator<< per il dato da stampare (nel nostro caso Patient) dara' errore
    while( tmp != NULL ){
        flusso_dati << "----dato---- " << endl;
        flusso_dati << tmp->data << endl; // ! E' QUESTA LA RIGA INCRIMINATA
        tmp = tmp->next;
    }
    

    flusso_dati << "Tail" << endl;

    return flusso_dati;
}

int main(int argc, char * argv[]){

    /*
    // OK, con gli interi funzionano sia l'operator<<  che l'enQueuePriority()
    int x = 1, y = 2, z = 3, k = 9, p = 120;
    Queue<int> coda;
    coda.enQueue(x);
    coda.enQueue(y);
    coda.enQueue(z);
    coda.enQueue(k);
    coda.enQueuePriority(p);

    cout << "Printiamo la coda" << endl;
    cout << coda;
    */


    int id;
    string name, condition;
    //string check_prior;
    //bool prior = false;
    
    cout << "Creiamo un paziente. \n"

    << "Inserisci id: ";
    cin >> id;
    cout << "Nome: ";
    cin >> name;
    cout << "Condizione: ";
    cin >> condition;
    //cout << "E' un paziente con priorita'? [y/n]: ";
    //cin >> check_prior;
    cout << "Ora creiamo il paziente\n";

    //if( check_prior == "y" || check_prior == "Y" ) prior = true;

    Patient p1 (id, name, condition);

    p1.stampa();
    
    Patient p2(11, "mike", "morbillo");
    Patient p3(22, "daniele", "atrosi");
    Patient p4(33, "martino", "influenza");
    Patient p5(44, "cleo", "varicella");
    Patient p6(55, "ginevra", "febbre");
    
    p2.stampa();

    Queue<Patient> coda;
    //cout << coda;
 
    //cout << "-----dovrebbe avermi stampato la lista vuota" << endl;

    cout << "Ora iniziamo l'inserimento" << endl;

    coda.enQueue(p1);
    coda.enQueue(p2);
    coda.enQueue(p4);
    coda.enQueue(p5);
    //cout << "stampiamo dopo i primi due inserimenti: " << coda;
    
    coda.enQueuePriority(p3); 
    cout << "STAMPA CODA POST enQueuePriority()" << endl << coda; // ! e qua iniziano i problemi

}