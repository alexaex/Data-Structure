#ifndef DATA_STRUCTURE_CONTAINER_H
#define DATA_STRUCTURE_CONTAINER_H
#include <iostream>

#define Max_Length 255
const int stk_capacity = 255;
typedef int datatype;



namespace container{



    //Seq_List
    typedef struct _seq_list{
        size_t len;
        datatype data[Max_Length];
        _seq_list():len(0){};
        _seq_list(size_t size):len(size){};
        _seq_list(std::initializer_list<datatype> ll);
        size_t size() const{return len;};
        bool is_empty(){return len;}
    }SeqList;
    void push_back(SeqList& List,datatype value);
    //push element onto the end of seq_list
    void remove_over_index(SeqList& List,size_t idx);
    //remove element via index
    void remove_over_value(SeqList& List,datatype value);
    //remove element via value
    int find(const SeqList& List, datatype value, size_t st_pos=0);
    //search element
    void insert(SeqList& List,size_t idx,datatype value);
    //insert element to the seq_list
    void traverse(const SeqList& List);




    //single linked node
    struct sll_node{
        sll_node* next;
        datatype data;

        sll_node():next(nullptr){};
        sll_node(datatype val):data(val),next(nullptr){};
    };

    typedef sll_node* sl_list;

    //check empty
    inline bool is_empty(const sl_list& head)
    {
        return head== nullptr;
    }

    void push_back(sl_list& root,datatype value);
    //push element onto the end of single_linked_node
    void traverse(sl_list root);

    sll_node* find(sl_list root,datatype value);
    //search element
    void insert_back(sll_node* & node ,datatype value);
    //insert element to the next of one node
    void pop_next(sll_node* & node);
    //pop the next node of current node
    void init_sll(sl_list& root,std::initializer_list<datatype>ll);
    //list initialize function
    void release(sl_list& root);
    //memory release
    //void reverse(sl_list& root);
    //void merge(sl_list& l1,sl_list& l2);



    //double_linked_list
    struct dl_node{
        dl_node* prev;
        dl_node* next;
        datatype data;
        dl_node():prev(nullptr),next(nullptr){};
        dl_node(datatype value):prev(nullptr),next(nullptr),data(value){};
    };

    typedef dl_node* dl_list;

    inline bool is_empty(const dl_list& root){
        return root== nullptr;
    }

    void insert_back(dl_node*& node, datatype value);
    void insert_front(dl_node*& node ,datatype value);
    void remove_via_value(dl_list& root, datatype value);
    void pop_prev(dl_node*& node);
    void pop_next(dl_node*& node);
    void init_dll(dl_list& root,std::initializer_list<datatype> ll);
    dl_node* find(dl_list root,datatype value);

    void release(dl_list& root);

    inline void traverse(dl_list list){
        while (list!= nullptr){
            printf("%d ",list->data);
            list = list->next;
        }
        std::endl(std::cout);
    }



    // circular linked list
    typedef sll_node* cir_list;
    // this is a circular linked list.
    void release_cir_list(cir_list& list);
    void init_cir_list(cir_list& list, std::initializer_list<datatype>);
    void traverse_cir_list(cir_list root);
    void cir_list_insert_back(sll_node*& node,datatype value);
    void cir_pop_next(sll_node*& node);
    sll_node* find_in_cir_list(cir_list root,datatype value);


    class linked_stack{
    private:
        struct node{
            node* next;
            datatype data;
            node(datatype val):next(nullptr),data(val){};
            explicit node():next(nullptr){};
        };
        node* _top{};
    public:
        linked_stack():_top(nullptr){};

        explicit linked_stack(datatype val){
            _top = new node(val);
        }

        linked_stack(std::initializer_list<datatype> ll);

        ~linked_stack(){
            this->release();
        }

        bool is_empty() const{
            return _top == nullptr;
        }

        void push(datatype val);

        void pop();

        datatype top(){
            if(this->is_empty()){
                printf("empty stack.\n");
                return 0b11111111;
            }
            return this->_top->data;
        }

        void release();

        void traverse()const {
            if(_top== nullptr)
                return;
            auto cur = _top;
            while (cur!= nullptr){
                printf("%d ",cur->data);
                cur = cur->next;
            }
            cur = nullptr;
            std::endl(std::cout);
        }

    };


    class seq_stack{
    private:
        int _top;
        datatype data[stk_capacity];
    public:
        seq_stack():_top(-1){};
        
        seq_stack(std::initializer_list<datatype> ll):_top(-1){
            if(ll.size()>=stk_capacity-1){
                printf("failed to initialize.\n");
                return;
            }
            for(auto element:ll){
                data[++_top] = element;
            }
        }
        
        bool is_empty()const{
            return _top==-1;
        }
        
        void push(const datatype& val){
            if(_top>=stk_capacity-1)
            {
                printf("full stack.\n");
                return;
            }
            this->data[++_top] = val;
        }
        
        void pop(){
            if(is_empty())
            {
                printf("empty stack.\n");
                return;
            }
            this->_top--;
        }
        
        datatype top(){
            if(is_empty()){
                printf("empty stack.\n");
                return 0b11111111;
            }
            return this->data[_top];
        }

        void traverse(){
            if(_top==-1){
                return;
            }

            do{
                printf("%d ",this->data[_top--]);
            } while (_top!=-1);
            std::endl(std::cout);
        }


    };

    class linked_queue{
    private:

        struct node{
            node* next;
            datatype data;
            node():next(nullptr){};
            explicit node(datatype val):data(val),next(nullptr){};
        };

        node* _front;
        node* _rear;
    public:
        linked_queue(){
            _front = new node;
            _rear = _front;
        }

        linked_queue(datatype val){
            _front = new node;
            _rear = new node(val);
            _front->next = _rear;
        }

        linked_queue(std::initializer_list<datatype> ll){
            _front = new node;
            auto cur = _front;
            for(auto element:ll){
                _rear = new node(element);
                cur->next = _rear;
                cur = cur->next;
            }
            cur = nullptr;
        }

        ~linked_queue(){
            this->release();
        }

        bool is_empty()const{
            return _front == _rear;
        }

        void push(datatype val){
            auto cur = new node(val);
            _rear->next = cur;
            _rear = cur;
        }

        void pop(){
            if(is_empty())
                return;
            auto cur = _front->next;
            _front->next = cur->next;
            if(cur == _rear) _rear = _front;
            delete cur,cur = nullptr;
        }

        datatype front(){
            if(is_empty())
                return 0b11111111;
            return _front->next->data;
        }

        void release(){
            if(is_empty())
                return;
            while (_front != _rear){
                auto cur = _front->next;
                _front->next = cur->next;
                if(cur == _rear) _rear = _front;
                delete cur;
                cur = nullptr;
            }
            delete _front;
            _front = _rear = nullptr;
        }

        void clear(){
            if(is_empty())
                return;
            while (_front != _rear){
                auto cur = _front->next;
                _front->next = cur->next;
                if(cur == _rear) _rear = _front;
                delete cur;
                cur = nullptr;
            }
        }

        void traverse(){
            if(is_empty())
                return;
            auto cur = _front->next;
            while (cur != _rear->next){
                printf("%d ",cur->data);
                cur = cur->next;
            }
            cur = nullptr;
            std::endl(std::cout);
        }
    };

    class seq_queue;























}























#endif //DATA_STRUCTURE_CONTAINER_H
