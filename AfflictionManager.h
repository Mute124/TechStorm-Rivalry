#pragma once
#include "Common.h"
#include "IScriptable.h"
#include "Affliction.h"
#include "InventoryManager.h"
#include "Registry.h"
#include <tinyxml2.h>


using namespace tinyxml2;

class AfflictionManager : public IScriptable {
    
    AfflictionManager(const char *file) {
        XMLDocument doc;
        doc.LoadFile(file);

        XMLElement* root = doc.RootElement();

        Affliction* aff = { 0 };

        int mapSize = 0;
        if (NULL != root) {
			XMLElement* affElements = root->FirstChildElement("Afflictions");
            if (NULL != affElements) {
				XMLElement* affElement = affElements->FirstChildElement("Affliction");

                while (affElement) {
                    XMLElement* name = affElement->FirstChildElement("name");

					XMLElement* tooltip = affElement->FirstChildElement("tooltip");

					XMLElement* description = affElement->FirstChildElement("description");

					XMLElement* icon = affElement->FirstChildElement("icon");

					XMLElement* implication = affElement->FirstChildElement("implication");

					XMLElement* severity = affElement->FirstChildElement("severity");

					XMLElement* affCauses = affElement->FirstChildElement("causes");

                    int causeIndex = 0;

                    while (affCauses) {
						XMLElement* affCause = affCauses->FirstChildElement("cause");

                        affCauses->NextSiblingElement("cause");
						causeIndex++;
                    }

					XMLElement* affTreatments = affElement->FirstChildElement("treatments");

                    int treatmentIndex = 0;

                    while (affTreatments) {
						XMLElement* affTreatment = affTreatments->FirstChildElement("treatment");

						aff->Treatments[treatmentIndex] = InventoryMan::itemMap[affTreatment->GetText()];
                    
                        affTreatments->NextSiblingElement("treatment");
                        treatmentIndex++;
                    }

					XMLElement* affAffects = affElement->FirstChildElement("affects");

					int affectIndex = 0;

					AfflictionAffect* affAffectData = { 0 };

                    while (affAffects) {
						XMLElement* affAffect = affAffects->FirstChildElement("affect");
                       
                    }

                    // TODO: Get causes, treatments, affects

					//aff = new Affliction(name->GetText(), tooltip->GetText(), description->GetText(), icon->GetText(), implication->GetText(), severity->IntText(), ));

                }

            }
        }
        
    }
    
	static inline std::map<const char*, Affliction*> afflictionMap;
	static inline std::vector<Affliction*> simpleAfflictionRegistry;

	static inline int afflictionCount = 0;

private:
    static inline int Register(Affliction* affliction) {
		afflictionMap[affliction->name] = affliction;

        int mapSize = static_cast<const int>(afflictionMap.size());
		afflictionMap[affliction->name]->id = &mapSize;

		simpleAfflictionRegistry.push_back(affliction);
        afflictionCount = mapSize;
        return mapSize;
    }

};

