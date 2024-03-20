#include "chrono/physics/ChLinkMotorRotationSpeed.h"
#include "chrono/physics/ChSystemNSC.h"
#include <stdio.h>
#include <stdlib.h>
void please() {
	using namespace chrono;

	GetLog() << " Example: create a physical system.. \n";

	// The physical system: it contains all physical objects.
	ChSystemNSC sys = ChSystemNSC(true);

	// Create a bunch of rigid bodies..
	// Note that we use shared pointers, so you don't
	// have to care about the deletion (never use delete.. for
	// objects managed with shared pointers! it will be automatic!)
	auto my_body_A = chrono_types::make_shared<ChBody>();
	auto my_body_B = chrono_types::make_shared<ChBody>();
	auto my_body_C = chrono_types::make_shared<ChBody>();

	// Create some markers..
	// Markers are 'auxiliary coordinate systems' to be added
	// to rigid bodies.
	// Again, note that they are managed by shared pointers.

	auto my_marker_a1 = chrono_types::make_shared<ChMarker>();
	auto my_marker_a2 = chrono_types::make_shared<ChMarker>();
	auto my_marker_b1 = chrono_types::make_shared<ChMarker>();
	auto my_marker_b2 = chrono_types::make_shared<ChMarker>();

	// You can create some forces too...
	auto my_force_a1 = chrono_types::make_shared<ChForce>();
	auto my_force_a2 = chrono_types::make_shared<ChForce>();

	// Check if shared pointers are valid
	if (!my_body_A || !my_body_B || !my_body_C ||
		!my_marker_a1 || !my_marker_a2 || !my_marker_b1 || !my_marker_b2 ||
		!my_force_a1 || !my_force_a2) {
		// Handle error, e.g., throw an exception or return from the function
		printf("failed");
		return; // Or throw an exception, depending on your error handling strategy
	}
	// Here you will add forces and markers to rigid
	// bodies.
	// Note: the same marker shouldn't be added to multiple bodies.
	my_body_A->AddMarker(my_marker_a1);
	my_body_A->AddMarker(my_marker_a2);
	my_body_A->AddForce(my_force_a1);
	my_body_A->AddForce(my_force_a2);
	my_body_B->AddMarker(my_marker_b1);
	my_body_B->AddMarker(my_marker_b2);

	// Ok, remember that rigid bodies must be added to
	// the physical system.
	sys.AddBody(my_body_A);
	sys.AddBody(my_body_B);
	sys.AddBody(my_body_C);

	// Show the hierarchy in the shell window...
	GetLog() << "Here's the system hierarchy which you built: \n\n ";
	sys.ShowHierarchy(GetLog());

	// Do you want to remove items? Use the
	// Remove...() functions.
	my_body_A->RemoveAllForces();

	// Remove a single body..
	sys.RemoveBody(my_body_A);

	// Add markers to another body...
	my_body_B->AddMarker(my_marker_a1);
	my_body_B->AddMarker(my_marker_a2);
	my_body_B->AddForce(my_force_a1);
	my_body_B->AddForce(my_force_a2);

	// By the way, you can set an Ascii name for objects as desired:
	my_marker_a1->SetName("JohnFoo");
	// ..so you can later use  my_body_B.SearchMarker("JohnFoo"); etc.

	GetLog() << "\n\n\nHere's the system hierarchy after modifications: \n\n ";
	sys.ShowHierarchy(GetLog());
}
