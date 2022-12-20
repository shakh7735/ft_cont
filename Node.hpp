#ifndef NODE_HPP
#define NODE_HPP

namespace ft{

    enum {BLACK = false, RED = true};
    template < class T > 
    struct		node
    {
        typedef T value_type;
        T                   	data;
        struct node *			left;
        struct node *			right;
        struct node *			parent;
        bool 					nil;
        bool					color;

        node (T data) : data(data),left(0), 
                right(0), parent (0), nil( true ), color( BLACK ) 
                {}
       
        node ( void )    :   data(0), left(0), 
                right(0), parent (0), nil(true), color( BLACK ) {}
    } ;

}

#endif