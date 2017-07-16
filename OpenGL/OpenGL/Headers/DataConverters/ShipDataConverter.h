#pragma once

#include "Memory/Handle.h"
#include "DataConverters/DataConverter.h"

using namespace CelesteEngine;


namespace SpaceGame
{

class ShipDataConverter : public DataConverter
{
  public:
    ShipDataConverter(const ConstHandle<Data>& dataFile);
    ShipDataConverter(const XMLElement* element);

  private:
    typedef DataConverter Inherited;

    void load(const XMLElement* element);

    STRING_DATA_ELEMENT(TextureRelativePath)
    FLOAT_DATA_ELEMENT(LinearSpeed)
    FLOAT_DATA_ELEMENT(AngularSpeed)
};

}