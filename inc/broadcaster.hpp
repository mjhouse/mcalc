/** @file

	@brief		The class definition file for the
				broadcaster class.

	@details 	Acts as a communication backbone for
				all interfaces, notifying all of them
				when one changes.

	@author Michael House
	@version 0.1 10/19/17
*/
#pragma once
#ifndef MCALC_BROADCASTER_HPP
#define MCALC_BROADCASTER_HPP

#include <vector>

namespace mc {

	class Subscriber;
	class Interface;
	class Event;

	/**
		The Broadcaster singleton class that acts
		as a communication channel for Interfaces.
	*/
	class Broadcaster {
		private:
			std::vector<Interface*> interfaces;
			std::vector<Subscriber*> subscribers;
			Broadcaster() : subscribers({}) {};

		public:
			static Broadcaster* get_instance();		/**< Get the singleton instance of broadcaster */
			~Broadcaster();							/**< The destructor */
			void subscribe(Interface* s);			/**< Subscribe an interface to receive notifications */
			void subscribe(Subscriber* s);			/**< Subscribe a subscriber to receive notifications */
			void broadcast(Event e);				/**< Broadcast an event to all subscribed interfaces */
	};

	/**
		Events maintain an event type and a pointer to the
		sender who produced the event.
	*/
	class Event {

		public:
			/** The type of the event instance */
			enum Type { ALL, SINGLE };

		private:
			Event::Type	event_type;
			Interface*	event_sender;

		public:
			/**
				Constructor with no sender, defaults the sender to nullptr
				@param t The type of the new event
			*/
			Event( Type t );

			/**
				Constructor with no type, defaults the type to ALL
				@param s The sender
			*/
			Event( Interface* s );

			/**
				Constructor with both type and sender.
				@param t The type of the new event
				@param s The sender
			*/
			Event( Type t, Interface* s );

			/** The destructor */
			~Event(){};

			/**
				Get the type of the instance
				@return The type of Event
			*/
			Event::Type type();

			/**
				Get a pointer to the sender
				@return The Interface that generated the event
			*/
			Interface* sender();
	};

}

#endif
