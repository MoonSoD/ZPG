#include "ShaderProgram.h"
#include "Camera.h"

ShaderProgram::ShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile) {
	ShaderLoader* loader = new ShaderLoader();
	id = loader->loadShader(vertexShaderFile, fragmentShaderFile);
}

void ShaderProgram::useProgram() {
	GLint uniformID = glGetUniformLocation(id, "textureUnitID");
	glUniform1i(uniformID, 0);

	glUseProgram(id);
}

void ShaderProgram::setCamera(Camera* camera) {
	this->camera = camera;
	this->camera->addObserver(this);
}

void ShaderProgram::updateCamera() {
	if (camera) {
		glUseProgram(id);
		GLint idViewMatrix = glGetUniformLocation(id, "viewMatrix");
		GLint idProjectionMatrix = glGetUniformLocation(id, "projectionMatrix");
		GLint idIsSkyboxLocked = glGetUniformLocation(id, "isSkyboxLocked");
		//GLint idSkyboxViewMatrix = glGetUniformLocation(id, "skyboxViewMatrix");

		if (idViewMatrix == -1 || idProjectionMatrix == -1) {
			// fprintf(stderr, "Couldn't find viewMatrix or projectionMatrix in shader\n");
			return;
		}

		glUniformMatrix4fv(idViewMatrix, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
		glUniformMatrix4fv(idProjectionMatrix, 1, GL_FALSE, glm::value_ptr(camera->getProjectMatrix()));
		glUniform1i(idIsSkyboxLocked, camera->getIsSkyboxLocked());

		glm::vec3 eye = camera->getEye();
		glm::vec3 target = camera->getTarget();


        // glm::mat4 skyboxViewMatrix = glm::mat4(glm::mat3(camera->getViewMatrix()));  // Only rotation, no translation

        // // Send the adjusted view matrix for the skybox
        // glUniformMatrix4fv(idSkyboxViewMatrix, 1, GL_FALSE, glm::value_ptr(skyboxViewMatrix));

		glUseProgram(0);

		this->updateLight(eye, target);
	}
}


void ShaderProgram::applyTransformation(glm::mat4 matrix) {
	glUseProgram(id);
	GLint idModelTransform = glGetUniformLocation(id, "modelMatrix");

	if (idModelTransform == -1) {
		// fprintf(stderr, "Couldn't find modelMatrix in shader");
	}

	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &matrix[0][0]);
	glUseProgram(0);
}


void ShaderProgram::updateLight(Light* light, int lightIndex) {
    glUseProgram(id); 

	// printf("Light index: %i\n", lightIndex);
	// printf("Light position: %f, %f, %f\n", light->getPosition().x, light->getPosition().y, light->getPosition().z);
	// printf("Light direction: %f, %f, %f\n", light->getDirection().x, light->getDirection().y, light->getDirection().z);
	// printf("Light ambient: %f, %f, %f\n", light->getAmbient().x, light->getAmbient().y, light->getAmbient().z);
	// printf("Light diffuse: %f, %f, %f\n", light->getDiffuse().x, light->getDiffuse().y, light->getDiffuse().z);
	// printf("Light specular: %f, %f, %f\n", light->getSpecular().x, light->getSpecular().y, light->getSpecular().z);
	// printf("Light color: %f, %f, %f\n", light->getColor().x, light->getColor().y, light->getColor().z);
	// printf("Light constantAttenuation: %f\n", light->getConstantAttenuation());
	// printf("Light linearAttenuation: %f\n", light->getLinearAttenuation());
	// printf("Light quadraticAttenuation: %f\n", light->getQuadraticAttenuation());

	glUniform1i(glGetUniformLocation(id, ("light[" + std::to_string(lightIndex) + "].type").c_str()), light->getType()); 
	glUniform3fv(glGetUniformLocation(id, ("light[" + std::to_string(lightIndex) + "].position").c_str()), 1, glm::value_ptr(light->getPosition()));
	glUniform3fv(glGetUniformLocation(id, ("light[" + std::to_string(lightIndex) + "].direction").c_str()), 1, glm::value_ptr(light->getDirection()));

	glUniform1f(glGetUniformLocation(id, ("light[" + std::to_string(lightIndex) + "].constantAttenuation").c_str()), light->getConstantAttenuation());
	glUniform1f(glGetUniformLocation(id, ("light[" + std::to_string(lightIndex) + "].linearAttenuation").c_str()), light->getLinearAttenuation());
	glUniform1f(glGetUniformLocation(id, ("light[" + std::to_string(lightIndex) + "].quadraticAttenuation").c_str()), light->getQuadraticAttenuation());

	glUniform1f(glGetUniformLocation(id, ("light[" + std::to_string(lightIndex) + "].cutoffAngle").c_str()), light->getCutoffAngle());

	glUseProgram(0);
}


void ShaderProgram::updateLight(glm::vec3& eye, glm::vec3& target) {
	glUseProgram(id);


	GLint idViewPosition = glGetUniformLocation(id, "viewPosition");
	GLint idLightPosition = glGetUniformLocation(id, "cameraTarget");


	if (idViewPosition == -1) {
		//fprintf(stderr, "Couldn't find viewPosition uniform for light in shader!");
		return;
	}

	glUniform3fv(idViewPosition, 1, glm::value_ptr(eye));
	glUniform3fv(idLightPosition, 1, glm::value_ptr(target));
	glUseProgram(0);
}

void ShaderProgram::applyMaterial(Material* material) {
	glUseProgram(id);
	
	auto ambient = glm::vec3(1.0f);
	auto diffuse = glm::vec3(1.0f);
	auto specular = glm::vec3(1.0f);
	auto color = glm::vec3(1.0f);

	if (material != nullptr) {
		ambient = material->getAmbient();
		diffuse = material->getDiffuse();
		specular = material->getSpecular();
		color = material->getColor();
	}

	GLint idColor = glGetUniformLocation(id, "objectColor");
	GLint idAmbient = glGetUniformLocation(id, "r_a");
	GLint idDiffuse = glGetUniformLocation(id, "r_d");
	GLint idSpecular = glGetUniformLocation(id, "r_s");

	if (idAmbient == -1 || idDiffuse == -1 || idSpecular == -1) {
		return;
	}

	glUniform3fv(idColor, 1, glm::value_ptr(color)); 
	glUniform3fv(idAmbient, 1, glm::value_ptr(ambient));
	glUniform3fv(idDiffuse, 1, glm::value_ptr(diffuse));
	glUniform3fv(idSpecular, 1, glm::value_ptr(specular));
	glUseProgram(0);
}

