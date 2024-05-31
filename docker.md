## First time setup

1. Run these commands

```bash
docker run -d --name pic-soc alpine:latest tail -f /dev/null
docker exec pic-soc /bin/sh -c "apk update && apk add --no-cache bison flex gcc g++ make git libc-dev"
```

This will install the required dependencies, and start the container.

2. Install the `Dev Containers` VSCode extension

3. Open VSCode, and press `Ctrl+Shift+P` and type `attach to running container`, and select the `Dev Containers: Attach to Running Container...` option.

4. Select the `pic-soc` container, and wait for the container to attach and a new VSCode window to open.
5. In the new window, press `Ctrl+J` to open the terminal, and run the following commands:

```bash
git clone https://github.com/abhijit424515/soc-python-interpreter-in-cpp
code soc-python-interpreter-in-cpp/
```

Close the old windows, and you are ready to start coding.

---

## How to start the container after the first time setup (if you have closed the container or rebooted)

1. Run these commands

```bash
docker start pic-soc
```

2. Follow the steps 3 and 4 from the first time setup.
3. In the new window, press `Ctrl+J` to open the terminal, and run the following commands:

```bash
code soc-python-interpreter-in-cpp/
```

Close the old windows, and you are ready to start coding.