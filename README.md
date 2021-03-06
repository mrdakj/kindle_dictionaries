# Kindle English-Language Dictionary Generator

## Usage

Input: target language

Output: dictionary.mobi (English - target language dictionary)

## Dokcer 

1. Clone this repository

    ```sh
	docker pull mrdakj/dictionary 

    ```

2. Create and run a container:

    ```sh
	docker run -it mrdakj/dictionary --shell

    ```
3. Get container name:

    ```sh
	docker ps -a

    ```
4. Copy generated dictionary from container to host:

    ```sh
	docker cp [container_name]:/dictionary.mobi .

    ```
## :package: Installation
:exclamation: Requirements: [range-v3](https://github.com/ericniebler/range-v3), [googletrans](https://pypi.org/project/googletrans/)

### Manual

1. Clone this repository

    ```sh
    git clone https://github.com/mrdakj/kindle_dictionaries.git

    ```
2. Compile

    ```sh
	cd kindle_dictionaries
	make

    ```

3. Start

    ```sh
	./run.sh

    ```
