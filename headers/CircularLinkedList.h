/***************************************************************************
* CircularLinkedList.h
* Defines a circular linked list for demonstration and evaluation purposes 
*	for students at Whitworth University's CS273: Data Structures class.
*	Students are assigned to complete the incomplete definition, in the
*	process exercising their understanding of template classes, pointers,
*	and sequential containers.
* 
* Author: Matthew Bell and CS273
* Co-authors: <TODO: PUT YOUR NAME HERE. YOU MAY WORK IN GROUPS OF TWO
				IFF you come to Prof. Bell for advice.>
* 
* Miscelleneous credits:
* This example is loosely based on an earlier doubly linked list (non-circular)
* developed by the CS faculty @ Whitworth University, particularly Wizard Dr.
* Kent Jones and Wizard Dr. Ed Walker!
*****************************************************************************/

#include <stdexcept>

#ifndef CLL_H
#define CLL_H

/****************************************************************************
* We define our own namespace, CS273, so that our circular linked list cannot 
* be confused with anything in namespace std
*****************************************************************************/
namespace CS273 {

	/****************************************************************************
	* CircLinkedList defines a circular linked list as a list of nodes.
	*****************************************************************************/
	template<class T>
	class CircLinkedList {
	private:
#pragma region NodeStruct
		/// <summary>
		/// class node defines the nodes of which this list consists
		/// </summary>
		struct node {
			node* next; // Pointer to the next node in the list
			node* prev; // Pointer to the previous node in the list
			T data;		// The actual data stored in this node

			/// <summary>
			/// Constructor for node minimally needs data to point to
			/// </summary>
			node(const T& data, node* after = nullptr) : data(data) {
				//If after isn't null, then we need to insert our new node in front
				if (after != nullptr) {
					next = after;
					prev = after->prev;
					after->prev->next = this;
					after->prev = this;
				}
				else {
					next = this;
					prev = this;
				}
			}
		};
#pragma endregion

		node* head;		// the "first" item in the list
		node* tail;		// the "last" item in the list
		int num_items;	// keeps track of the total number of items

	public:
#pragma region Iterator
		/// <summary>
		/// The iterator for our circular linked list acts like a "line manager"
		/// for the class. Access to data stored in the list is mediated entirely
		/// via these iterators. (Note: iterators are public, nodes are private!)
		/// </summary>
		class iterator {
		private:
			CircLinkedList<T>* parent;	// The list this iterator belongs to
			node* cur;					//The current node this iterator points to

			/// <summary>
			/// The iterator for CircLinkedList has access to CircLinkedList's private
			/// data.
			/// </summary>
			friend class CircLinkedList<T>;
		public:
			iterator(CircLinkedList<T>* parent = nullptr, node* cur = nullptr) :
				parent(parent), cur(cur) {}

			///
			/// Overloaded operators for advancing and for moving backwarts
			/// 
			// iterator& operator++() {
			// 	//TODO
			// }
			// iterator& operator--() {
			// 	//TODO
			// }

			///
			/// Overloaded dereferencing operator for treating an iterator like
			/// a pointer.
			/// 
			T& operator*() {
				return cur->data;
			}

			///
			/// Overloaded == and != to allow for comparing two iterators
			/// 
			bool operator==(const iterator& alt) {
				return (cur == alt.cur);
			}
			bool operator!=(const iterator& alt) {
				return cur != alt.cur;
			}
		};

#pragma endregion

		///
		/// Constructor for the list
		/// 
		CircLinkedList<T>() : head(nullptr), tail(nullptr), num_items(0) {}
#pragma region StandardFunctionality

		///
		/// Linked lists of all sorts can be accessed in various ways. For this version, we
		/// implement a subset of the interface for the STL linked list. A major different
		/// is that, because this list is circular, it doesn't make sense to return an
		/// iterator to end. 
		/// 
		/// Member methods to be implemented for this interface:
		/// front (returns a reference to the data in the first element)
		/// back (returns the data in the last element)
		/// begin (returns an iterator to the first element)
		/// empty (returns true if empty)
		/// size (returns the number of elements)
		/// clear (empties the list!)
		/// insert (inserts before an element using an iterator to indicate where)
		/// erase (opposite of insert!)
		/// push_back (inserts at the end)
		/// pop_back (removes from the end)
		/// push_front (inserts at the beginning)
		/// pop_front (removes from the beginning)
		/// 
		
		T& front() {
			if (num_items == 0)
				throw std::out_of_range("list empty");
			return head->data;
		}

		T& back() {
			if (num_items == 0)
				throw std::out_of_range("list empty");
			return tail->data;
		}

		/// <summary>
		/// begin returns an iterator to the beginning of the list, but...
		/// </summary>
		/// <returns>
		/// This requires some explanation! Straightforward if the list has
		/// elements, but, if it is empty, it returns an iterator that doesn't
		/// point anywhere (so to nullptr)!
		/// </returns>
		iterator begin() {
			iterator it(this, head);
			return it;
		}

		bool empty() const {
			return num_items == 0;
		}

		int size() const {
			return num_items;
		}

		void clear() {
			node* byebye = head;
			for (int i = 0; i < num_items; ++i) {
				node* forever = byebye;
				byebye = byebye->next;
				delete forever;
			}
			num_items = 0;
		}

		/// <summary>
		/// Most of the time, insert is pretty straightforward, but, if the
		/// list is empty, it has to treat the special case of insertion
		/// at the beginning. Also, if the proposed location doesn't make
		/// sense, e.g. isn't in this list, then don't insert.
		/// </summary>
		/// <param name="pos">pos is the point before which to insert</param>
		/// <param name="value">value is a reference to what is inserted</param>
		iterator insert(iterator pos, const T& value) {
			//Step 0: make a blank iterator to this. That way, we have something
			//to return even in a worst case. Note this means that a "broken"
			//iterator will be returned.
			iterator it(this);
			
			//First, make sure the insertion point makes sense!
			if (pos.parent == this) {
				//It makes sense, so get a node started...
				node* elem = nullptr;
				//Second, see if we're not in the special case of insertion at
				//the beginning
				if (!empty()) {
					elem = new node(value, pos.cur);

					//Update front if we need to
					if (pos.cur == head)
						head = elem;
				}
				else {
					//We are in the special case!
					elem = new node(value);
					elem->next = elem;
					elem->prev = elem;
					head = elem;
					tail = elem;
				}
				num_items++;
				it.cur = elem;
			} 
			// OK, insertion done. Return that iterator, which will be nonsense
			// if the insertion point didn't make sense.
			return it;
		}

		/// <summary>
		/// For erase, we partly depart from the spirit of the STL's erase.
		/// Ours isn't quite so sophisticated -- returns a void rather than
		/// an iterator. Otherwise, much is the same as for insert.
		/// WARNING: a side effect of this is that the iterator passed in
		///		is now invalid!
		/// </summary>
		/// <param name="pos">The position from which to erase.</param>
		void erase(iterator pos) {
			//Check to make sure the position makes sense!
			if (num_items > 0 && pos.parent == this) {
				//It does, so delete away! First, check if we're deleting
				//from the end and, if so, update back.
				if (pos.cur == tail)
					tail = pos.cur->prev;
				//Second, check if we're deleting from the front and, if so,
				//update front.
				if (pos.cur == head)
					head = pos.cur->next;

				//Now we can delete away!
				node* byebye = pos.cur;
				byebye->next->prev = byebye->prev;
				byebye->prev->next = byebye->next;
				delete byebye;
				num_items--;
			}
		}

		/// <summary>
		/// Puts an element at the "end" of the list, which should then
		/// point to the beginning. In the special case where nothing is
		/// in the list currently, should point to itself.
		/// </summary>
		/// <param name="value">The item being inserted</param>
		void push_back(const T& value) {
			node* elem;
			if (num_items > 0) {
				elem = new node(value, head);
			}
			else {
				//We're in the special case of an empty list
				elem = new node(value);
				elem->next = elem;
				elem->prev = elem;
				head = elem;
			}
			num_items++;
			tail = elem;
		}

		/// <summary>
		/// Removes an element from the "back" of the list, causing the
		/// previous element before it to point to the beginning.
		/// </summary>
		void pop_back() {
			// do nothing if empty
			if (num_items == 0)
				return;

			// if one item, empty the whole list
			if (num_items == 1) {
				delete head; 	// deallocate
				head = nullptr;	// null is a sin against god, but its the default for empty lists
				tail = nullptr;
				num_items--;	// decrement the count
				return;			// return so it doesn't continue to default process
			}

			node* byebye = tail;   // We need to deallocate tail, but first it must be reasigned
			tail = tail->prev;     // poping off the last item makes the previous to last the new last item

			// finish the circle
			tail->next = head;
			head->prev = tail;

			delete byebye;  // Now safely deletes the old tail
			num_items--;	// decrement the count
		}


		/// <summary>
		/// Adds an element to the "front" of the list, causing the
		/// next element after it to point to the end.
		/// </summary>
		void push_front(const T& value) {
			node* elem;
			if (num_items > 0) {
				// pointing to after handles all other prev and nexts through the node constructor
				elem = new node(value, head);
			}
			else {
				// in case of empty list
				elem = new node(value);
				elem->next = elem;
				elem->prev = elem;
				tail = elem;
			}
			num_items++; // increment for push
			head = elem; // set head (otherwise it would just act as an inbetween of head and tail)
		}

		/// <summary>
		/// Removes an element from the "front" of the list, causing the
		/// next element after it to point to the end.
		/// </summary>
		void pop_front() {
			if (num_items == 0)
				return;

			// if one item, empty the whole list
			if (num_items == 1) {
				delete head; 	// deallocate
				head = nullptr;	// null is a sin against god, but its the default for empty lists
				tail = nullptr;
				num_items--;	// decrement the count
				return;			// return so it doesn't continue to default process
			}

			node* byebye = head;   // We need to deallocate tail, but first it must be reasigned
			head = head->next;     // poping off the last item makes the previous to last the new last item

			// finish the circle
			head->prev = tail;
			tail->next = head;

			delete byebye;  // Now safely deletes the old tail
			num_items--;	// decrement the count
		}

#pragma endregion
#pragma region RuleOfThree
		///TODO:
		/// Recall: the Rule of Three requires that we define a destructor,
		/// a copy constructor, and an overloaded assignment operator!
		/// 
		/// First, the destructor
		virtual ~CircLinkedList<T>() {
			//March through the list destroying the whole thing!
			node* byebye = head;
			while (num_items > 0) {
				node* forever = byebye;
				byebye = byebye->next;
				delete forever;
				num_items--;
			}
		}
		///TODO
		/// <summary>
		/// The copy constructor makes a deep copy
		/// </summary>
		///CircLinkedList<T>(const CircLinkedList<T>& alt) :
		///	head(nullptr), tail(nullptr), num_items(0) {
		///	
		///	node* n = alt.head;
		///	int items_copied = 0;
		///	while (items_copied < alt.num_items) {
				//TODO
		///	}
		///}
	};
};
#endif
#pragma endregion