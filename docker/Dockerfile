FROM ubuntu:20.04

ENV TZ=Europe/Budapest
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update && apt-get install --no-install-recommends -y \
	make \
	doxygen \
	graphviz \
	&& apt-get install -y git \
	valgrind \
	cppcheck \
	libgtest-dev \
	cmake \
	g++ \
	g++-10 \
&& rm -rf /var/lib/apt/lists/*