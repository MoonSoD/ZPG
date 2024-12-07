#include <string>
#include "Model.h"

class ModelFactory {
public:
    static Model* createModel(std::string modelName);
};