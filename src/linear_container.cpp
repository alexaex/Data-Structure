#include "linear_container.h"

static auto max = [](auto const & x,auto const & y)->auto{return x>y?x:y;};

/************************************************
 ******************Seq_List**********************
 ************************************************/

container::_seq_list::_seq_list(std::initializer_list<datatype> ll) {
    if(ll.size()>=Max_Length)
        return;
    len = 0;
    for(datatype element:ll){
        data[len] = element;
        len++;
    }
}

void container::push_back(SeqList &List, datatype value) {
    if(List.len>=Max_Length-1)
    {
        printf("faild to exec push_back due to out of capacity.\n");
        return;
    }
    List.data[List.len] = value;
    List.len++;
}

void container::remove_over_index(SeqList &List, size_t idx) {
    if(idx>=Max_Length){
        printf("invalid index.\n");
        return;
    }
    if(List.len==0) return;
    for(size_t i = idx;i<List.len-1;i++)
        List.data[i] = List.data[i+1];
    List.len--;
}

void container::remove_over_value(SeqList &List, datatype value) {
    size_t idx = 0;
    for(;idx<List.len;idx++){
        if(List.data[idx] == value)
            break;
    }
    if(idx==List.len){
        printf("element doesn't exist.\n");
        return;
    }
    for(size_t i = idx;i<List.len-1;i++)
        List.data[i] = List.data[i+1];
    List.len--;
}

void container::insert(SeqList &List, size_t idx, datatype value) {
    if(List.len>=Max_Length){
        printf("out of capacity.\n");
        return;
    }
    idx = max(idx,0);
    if(idx>=List.len)
        List.data[List.len] = value;
    else{
        for(size_t j = List.len;j>idx;j--)
            List.data[j] = List.data[j-1];
        List.data[idx] = value;
    }
    List.len++;
}

void container::traverse(const SeqList& List) {
    for(size_t i = 0;i<List.len;i++){
        printf("%d ",List.data[i]);
    }
    std::cout<<std::endl;
}

int container::find(const SeqList& List, datatype value, size_t st_pos) {
    if(List.len==0){
        return -1;
    }
    if(st_pos>=List.len){
        printf("invalid start position.\n");
        return -2;
    }
    size_t j;
    for(j = max(0,st_pos);j<List.len;j++)
        if(List.data[j]==value)
            break;
    return (int)j;
}


/************************************************
 ******************Single_linked_list************
 ************************************************/

void container::traverse(sl_list root) {
    if(root== nullptr)
        return;
    root = root->next;
    while (root!= nullptr){
        printf("%d ",root->data);
        root = root->next;
    }
    printf("\n");
}

void container::push_back(sl_list &root, datatype value) {

    if(root == nullptr){
        root = new sll_node(value);
        return;
    }

    auto cur = root;

    while (cur->next!= nullptr){
        cur = cur->next;
    }
    cur->next = new sll_node(value);
}

void container::insert_back(sll_node* &node, datatype value) {

    if(node == nullptr){
        printf("invalid node.\n");
        return;
    }

    auto cur = new sll_node(value);
    cur->next = node->next;
    node->next = cur;

}

void container::pop_next(sll_node* &node) {
    if(node== nullptr){
        printf("invalid node to exec pop.\n");
        return;
    }
    auto cur = node->next;
    if(cur== nullptr)
        return;
    else
        node->next = cur->next;
    delete cur;
    cur = nullptr;
}

container::sll_node* container::find(sl_list root, datatype value) {
    if(root == nullptr)
        return nullptr;

    root = root->next;
    while (root!= nullptr){
        if(root->data == value)
            return root;
        else
            root = root->next;
    }
    return nullptr;
}

void container::release(sl_list &root) {
    if(root== nullptr)
        return;
    sll_node* cur;
    while (root!= nullptr){
        cur = root;
        root = cur->next;
        delete cur;
    }
    cur = nullptr;
    delete root;
    root = nullptr;
}

void container::init_sll(sl_list &root, std::initializer_list<datatype> ll) {
    if(root!= nullptr)
        container::release(root);
    root = new sll_node;
    auto cur = root;
    for(auto element:ll){
        cur->next = new sll_node(element);
        cur = cur->next;
    }
    cur = nullptr;
}

/*
void container::reverse(sl_list& root){
    if(root== nullptr)
        return;
    auto cur = root->next;
    sll_node* tmp = nullptr;
    while (cur!= nullptr){
        tmp = cur->next;
        cur->next = tmp;

        tmp = cur;
        cur = tmp;
    }
}
*/



/************************************************
 ******************Double_linked_list************
 ************************************************/


void container::insert_back(dl_node *&node, datatype value) {

    if(node== nullptr) {
        printf("invalid node.\n");
        return;
    }

    auto* tmp = new dl_node(value);
    auto next = node->next;
    if(next != nullptr) next->prev = tmp;
    tmp->next = next;
    tmp->prev = node;
    node->next = tmp;

}

void container::insert_front(dl_node *&node, datatype value) {

    if(node== nullptr)
        return;

    auto* tmp = new dl_node(value);

    auto prev= node->prev;
    tmp->next = node,node->prev = tmp;
    if(prev != nullptr){
        prev->next = tmp;
        tmp->prev = prev;
    }else prev = tmp;

}

void container::remove_via_value(dl_list &root, datatype value) {
    auto cur = root;
    while (cur!= nullptr){
        if(cur->data==value)
            break;
        cur = cur -> next;
    }
    if(cur == nullptr){
        printf("the value not exists in the list.\n");
        return;
    }
    if(cur == root){
        root = root->next;
        delete cur;
        return;
    }
    auto prev = cur->prev,next = cur->next;
    if(prev!= nullptr)
        prev->next = next;
    if(next!= nullptr)
        next->prev = prev;
    delete cur;
    cur = nullptr;
}

void container::pop_prev(dl_node *&node) {
    if(node== nullptr||node->prev== nullptr)
        return;
    auto prev = node->prev;
    prev->prev->next = node;
    node->prev = prev->prev;
    delete prev;
    prev = nullptr;
}

void container::pop_next(dl_node *&node) {
    if(node == nullptr || node->next == nullptr)
        return;
    auto next = node->next;
    next->next->prev = node;
    node->next = next->next;
    delete next;
    next = nullptr;
}

container::dl_node* container::find(dl_list root, datatype value) {
    if(root== nullptr)
        return nullptr;
    while (root!= nullptr){
        if(root->data == value)
            return root;
        root = root->next;
    }
    return nullptr;
}

void container::release(dl_list &root) {
    if(root== nullptr)
        return;
    dl_node* cur =  nullptr;
    while (root!= nullptr){
        cur = root;
        root = cur->next;
        delete cur;
    }
    cur = nullptr;
    root = nullptr;
}

void container::init_dll(dl_list &root, std::initializer_list<datatype> ll) {

    if(root!= nullptr){
        release(root);
    }
    if(root!= nullptr){
        printf("failed to initialize this list.\n");
        return;
    }
    root = new dl_node(*ll.begin());
    auto cur = root;
    for(auto itr = ll.begin()+1;itr!=ll.end();itr++){
        auto tmp = new dl_node(*itr);
        cur->next = tmp,tmp->prev = cur;
        cur = cur->next;
        tmp = nullptr;
    }
    cur = nullptr;
}


/************************************************
 ******************Circular_linked_list**********
 ************************************************/

void container::init_cir_list(cir_list &list, std::initializer_list<datatype> ll ) {
    if(list!= nullptr)
        //container::release(list);
        container::release_cir_list(list);
    if(list!= nullptr){
        printf("failed to initialize this circular linked list.\n");
        return;
    }

    for(auto element:ll){
        container::cir_list_insert_back(list,element);
    }

}

void container::traverse_cir_list(cir_list root){
    if(root== nullptr)
        return;
    auto cur = root;
    do{
        printf("%d ",cur->data);
        cur = cur->next;
    } while (root!=cur);
    cur = nullptr;
    std::endl(std::cout);
}

container::sll_node* container::find_in_cir_list(cir_list root,datatype value) {
    if(root == nullptr)
        return nullptr;
    auto cur = root;
    do{
        if(cur->data == value){
            return cur;
        }
        cur = cur->next;
    } while (cur!=root);
    return nullptr;
}

void container::cir_list_insert_back(sll_node *&node, datatype value) {
    auto tmp = new sll_node(value);
    if(node== nullptr) tmp->next = tmp,node = tmp;
    else
        tmp->next = node->next,node->next = tmp;
}

void container::cir_pop_next(sll_node *&node) {
    if(node== nullptr)
        return;
    auto cur = node->next;
    if(cur!=node){
        node->next = cur->next;
        delete cur,cur= nullptr;
        return;
    }
    else{
        node = nullptr;
        delete cur;
        return;
    }
}

void container::release_cir_list(cir_list &list) {
    while (list!= nullptr)
        cir_pop_next(list);
    list = nullptr;
}


/************************************************
 ******************Linked_stack******************
 ************************************************/


container::linked_stack::linked_stack(std::initializer_list<datatype> ll) {
    if(_top!= nullptr)
        this->release();
    for(auto element:ll){
        this->push(element);
    }
}

void container::linked_stack::push(datatype val) {
    if(this->_top== nullptr){
        _top = new node(val);
        return;
    }
    auto tmp = new node(val);
    tmp->next = this->_top;
    this->_top = tmp;

}

void container::linked_stack::pop() {
    auto cur = this->_top;
    this->_top = cur->next;
    delete cur;
    cur = nullptr;
}

void container::linked_stack::release() {
    if(_top== nullptr)
        return;
    node* cur;
    while (_top!= nullptr){
        cur = _top;
        _top = cur->next;
        delete cur;
    }
    cur = nullptr;
}
