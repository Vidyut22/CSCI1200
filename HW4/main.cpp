// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================
using namespace std;
#include <cassert>
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "order.h"
#include "item.h"

typedef list<Order> OrderList;
typedef list <Item> KitchenList;
//Needed for CanFillOrder()
typedef std::list <KitchenList::const_iterator> OrderFillList;

//Helper function
//Returns true if order can be fulfilled, and false otherwise. If true, then
//items_to_remove has iterators to kitchen_completed for all items that are used 
//in the order.
bool CanFillOrder(const Order &order, const KitchenList &kitchen_completed,
                  OrderFillList &items_to_remove);

int main() 
{
  OrderList orders;
  KitchenList food_cooking;
  KitchenList food_completed;
  std::string token;
  while (std::cin >> token) 
  {
    // Adds order to sorted list of other orders
    if (token == "add_order") 
    {
      int id, promised_time, n_items = 0;
      std::string next_item;
      std::list <std::string> order_items;

      std::cin >> id >> promised_time >> n_items;
      assert(n_items > 0);
      cout << "Received new order #" << id << " due in " << promised_time << " minute(s):" << endl;

      // Add each item in order
      for (int i = 0; i < n_items; i++) 
      {
        std::cin >> next_item;
        order_items.push_back(next_item);
        cout << "  " << next_item << endl;
      }
      orders.push_back(Order(id, promised_time, n_items, order_items));
      //Keep all orders sorted every time a new one gets added
      orders.sort(sortOrders);
    } 

    // Adds item to list of items being cooked
    else if (token == "add_item") 
    {
      int cook_time = -1;
      std::string name;
      std::cin >> cook_time >> name;
      assert(cook_time >= 0);

      //Add Item with amount of time to cook and name of item
      food_cooking.push_back(Item(cook_time, name));

      //Keep all items sorted every time a new one gets added
      food_cooking.sort(sortItems);
      cout << "Cooking new " << name << " with " << cook_time << " minute(s) left." << endl;
    } 

    // Prints out all orders and items within, sorted by their time
    else if (token == "print_orders_by_time") 
    {
        cout << "Printing " << orders.size() << " order(s) by promised time remaining:" << endl;
        //Calls helper method to print (list orders is already sorted by time)
        printOrders(orders);
    } 

    // Print out all orders and items withn, sorted by their ID number
    else if (token == "print_orders_by_id") 
    {
        //Sort a copy of orders by id number (don't want to change original sorting patern)
        OrderList idOrders = orders;
        idOrders.sort(sortOrdersID);

        cout << "Printing " << idOrders.size() << " order(s) by ID:" << endl;
        //Calls helper method to print
        printOrders(idOrders);
    } 

    // Print out all items currently being cooked
    else if (token == "print_kitchen_is_cooking") 
    {
        cout << "Printing " << food_cooking.size() << " items being cooked:" << endl;

        //Looping all items
        for (KitchenList::iterator i = food_cooking.begin(); i != food_cooking.end(); i++)
        {
            cout << "  " << (*i).getItem() << " (" << (*i).getTime() << " minute(s) left)" << endl;
        }
    } 

    // Print out all items finished cooking
    else if (token == "print_kitchen_has_completed") 
    {
        cout << "Printing " << food_completed.size() << " completely cooked items:" << endl;

        //Looping all items
        for (KitchenList::iterator i = food_completed.begin(); i != food_completed.end(); i++)
        {
            cout << "  " << (*i).getItem() << endl;
        }
    } 

    //Run kitchen and complete all events within given amount of time
    //Events are completed in following order
    // 1) Items getting completed
    // 2) Order gets filled
    // 3) Order time expires
    else if (token == "run_for_time") 
    {
      int run_time = 0;
      std::cin >> run_time;
      assert(run_time >= 0);
      cout << "===Starting run of " << run_time << " minute(s)===" << endl;
      
      //Used in CanFillOrder to determine items to remove
        OrderFillList items_to_remove;

        int iterate = 0;
        //Loop for amount of time requested (check if item finished cooking)
        while (iterate < run_time || run_time == 0)
        {
            KitchenList::iterator coItr = food_cooking.begin();
            //Loop all items cooking
            while (coItr != food_cooking.end())
            {
                if ((*coItr).getTime() != 0)
                {
                    //Decrease time to cook for item by 1 minute
                    if (run_time!=0)
                    {
                        (*coItr).updateTime();
                    }
                }
                //Check if item completed cooking
                if ((*coItr).getTime() == 0)
                {
                    cout << "Finished cooking " << (*coItr).getItem() << endl;

                    // Add item to completed list and erase from cooking
                    food_completed.push_back(*coItr);
                    coItr = food_cooking.erase(coItr);
                }
                else
                {
                    coItr++;
                }
            }

            //Loop all orders (check for order fill)
            OrderList::iterator orItr = orders.begin();
            while (orItr != orders.end())
            {
                //Helper method to check for order fill
                if (CanFillOrder((*orItr), food_completed, items_to_remove))
                {
                    cout << "Filled order #" << (*orItr).getId() << endl;

                    //Loop through all items taken by order
                    for (OrderFillList::iterator k = items_to_remove.begin(); k != items_to_remove.end(); k++)
                    {
                        //Print and remove items from completed list if taken by order
                        cout << "Removed a " << (**k).getItem() << " from completed items." << endl;
                        food_completed.erase(*k);
                          
                    }

                    //Delete order from orders if it got filled
                    orItr = orders.erase(orItr);
                }
                else
                {
                    orItr++;
                }
            }
            //Loop through all order (check if order expired)
            orItr = orders.begin();
            while (orItr != orders.end())
            {
                if ((*orItr).getTimeRemaining() != 0)
                {
                    // Decrease time remaining by 1
                    if (run_time != 0)
                    {
                        (*orItr).updateTimeRemaining();
                    }
                }
                // Check if order has expired
                if ((*orItr).getTimeRemaining() == 0)
                {
                    //Print and removed order form list of orders
                    cout << "Order # " << (*orItr).getId() << " expired." << endl;
                    orItr = orders.erase(orItr);
                }
                else
                {
                    orItr++;
                }
            }
            //Only loop once if run time was 0
            if (run_time == 0)
            {
                break;
            }
            iterate++;
        }
      cout << "===Run for specified time is complete===" << endl;
    } 
    //Run kitchen until a single event gets completed
    //Events are completed in following order
    // 1) Items getting completed
    // 2) Order gets filled
    // 3) Order time expires
    // If no events are possible, end and print message
    else if (token == "run_until_next") 
    {
    //Keep track of time in kitchen
      int time = 0;

      //Used in CanFillOrder to determine items to remove
      OrderFillList items_to_remove;
      std::cout << "Running until next event." << std::endl;

      //If there are no orders or food cooking, no events are possible
      if (orders.size() == 0 && food_cooking.size() == 0)
      {
          cout << "No events waiting to process." << endl;
      }
      else
      {
          //Bool to keep track if event has been completed within loop
          bool goOn = true;
          while (goOn)
          {
              //increment time spent
              time++;

              //Loop through all items currently cooking
              KitchenList::iterator coItr = food_cooking.begin();
              while (coItr != food_cooking.end())
              {
                  //Decrease time to cook by 1 minute
                  if ((*coItr).getTime() != 0)
                  {
                      (*coItr).updateTime();
                  }
                  else
                  {
                      if (goOn)
                      {
                          time--;
                      }
                  }
                  if (goOn)
                  {
                      //Check if time to cook item is equal to 0
                      if ((*coItr).getTime() == 0)
                      {
                          cout << "Finished cooking " << (*coItr).getItem() << endl;
                          // Add item to completed list and delete it from cooking list
                          food_completed.push_back(*coItr);
                          coItr = food_cooking.erase(coItr);
                          //Event Complete
                          goOn = false;
                          if (time == 0)
                          {
                              break;
                          }

                      }
                      else
                      {
                          coItr++;
                      }
                  }
                  else
                  {
                      coItr++;
                  }
                  
              }
              //Loop through all orders (Check if order can be filled)
              OrderList::iterator orItr = orders.begin();
              if (goOn)
              {
                  while (orItr != orders.end())
                  {
                      //Helper method to check for order fill
                      if (CanFillOrder((*orItr), food_completed, items_to_remove))
                      {
                          cout << "Filled order #" << (*orItr).getId() << endl;
                          //Loop through all items taken by order
                          for (OrderFillList::iterator k = items_to_remove.begin(); k != items_to_remove.end(); k++)
                          {
                              //Print and remove items from completed list if taken by order
                              cout << "Removed a " << (**k).getItem() << " from completed items." << endl;
                              food_completed.erase(*k);
                          }
                          orItr = orders.erase(orItr);
                          //Event Complete
                          goOn = false;
                          break;
                      }
                      else
                      {
                          orItr++;
                      }
                  }
              }
              //Loop through all order (check if order expired)
              if (goOn)
              {            
                    orItr = orders.begin();
                    while (orItr != orders.end())
                    {
                        //Decrease time remaining by 1 minute
                        if ((*orItr).getTimeRemaining() != 0)
                        {
                            (*orItr).updateTimeRemaining();
                        }
                        else
                        {
                            if (goOn)
                            {
                                time--;
                            }
                        }
                        if (goOn)
                        {
                            //Check if order has expired
                            if ((*orItr).getTimeRemaining() == 0)
                            {
                                //Print and removed order form list of orders
                                cout << "Order # " << (*orItr).getId() << " expired." << endl;
                                orItr = orders.erase(orItr);
                                //Event Complete
                                goOn = false;

                            }
                            else
                            {
                                orItr++;
                            }
                        }
                        else
                        {
                            orItr++;
                        }
                    }
              }
              //If event has already been completed, time on orders still need to be updated
              else
              {
                  //Loop through all orders
                  orItr = orders.begin();
                  while (orItr != orders.end())
                  {
                      //Decrease total time remaining on order by 1 minute
                      if ((*orItr).getTimeRemaining() != 0 && time !=0)
                      {
                          (*orItr).updateTimeRemaining();
                      }
                      orItr++;
                  }
              }
          }
          //Report total minutes passed in kitchen
          cout << time << " minute(s) have passed." << endl;
      }
    }
  }
  //Clear all orders
  orders.clear();
  return 0;
}


bool CanFillOrder(const Order &order, const KitchenList &kitchen_completed,
                  OrderFillList &items_to_remove) 
{
  items_to_remove.clear(); //We will use this to return iterators in kitchen_completed

  //Simple solution is nested for loop, but I can do better with sorting...

  std::list <std::string> order_items = order.getItems();
  order_items.sort();

  std::list<std::string>::const_iterator item_it;
  std::string prev_item = "";
  KitchenList::const_iterator kitchen_it;

  for (item_it = order_items.begin(); item_it != order_items.end(); item_it++) {
    bool found = false;

    /*Start back at beginnging of list if we're looking for something else
     *Thanks to sorting the order_items list copy, we know we're done with
       whatever kind of item prev_item was!*/
    if (prev_item != *item_it) {
      kitchen_it = kitchen_completed.begin();
      prev_item = *item_it;
    }

    /*Resume search wherever we left off last time (or beginning if it's a
    new kind of item*/
    for (; !found && kitchen_it != kitchen_completed.end(); kitchen_it++) {
      if (kitchen_it->getItem() == *item_it) {
        items_to_remove.push_back(kitchen_it);
        found = true;
      }
    }

    //If we failed to satisfy an element of the order, no point continuing the search
    if (!found) {
      break;
    }
  }

  //If we couldn't fulfill the order, return an empty list
  if (items_to_remove.size() != order_items.size()) {
    items_to_remove.clear();
    return false;
  }

  return true;
}

