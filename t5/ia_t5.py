from matplotlib.pyplot import plot

import numpy as np

from neupy import environment, algorithms, layers, plots

from sklearn import metrics
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import OneHotEncoder, MinMaxScaler

import theano

theano.config.floatX = 'float32'

digitos = np.loadtxt('exdata.csv', delimiter=',')

# PREPARAÇÃO DOS DADOS : -------------------------------------------------------
# Remove o valor que representa a classifição do digito, ou seja, remove a
# última linha da matriz de dados lida. O ".T" é responsável por transpor a
# matriz de dados
data = digitos[:-1].T

# Extrai as classificações(alvos) dos dígitos representados no arquivo de dados.
target = digitos[-1]

# Procurar pelos valores de classificação(alvo) igual a 10 e os mapeia para 0.
target[target == 10] = 0

# Normalização dos dados será realizada utilizando o MinMaxScaler do 
# scikit-learn, que é uma API de análise de dados em python.
# Será utlizado o método "fit_transform" da classe MinMaxScaler para realizar a
# normalização. Esse método de normalização mapeia os dados para um intervalo
# definido pelo usuário, e possui o intervalo de 0 a 1 como padrão.
# http://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.MinMaxScaler.html
min_max_scaler = MinMaxScaler()
data = min_max_scaler.fit_transform(data)

target_scaler = OneHotEncoder()
print(target)
target = target_scaler.fit_transform(target.reshape((-1, 1)))
print(target)
target = target.todense()


# CONFIGURAÇÕES DE AMBIENTE: ---------------------------------------------------
environment.reproducible()

# SEPARAÇÃO DE DADOS PARA TREINO E TESTE:
data_train, data_test, target_train, target_test = train_test_split(
    data,
    target,
    train_size=(6. / 7),
    test_size=(1. / 7)
)

# CRIAÇÃO DA REDE NEURAL:
network = algorithms.Momentum(
    [
        layers.Input(400),
        layers.Relu(32),
        layers.Relu(300),
        layers.Softmax(10),
    ],
    error='categorical_crossentropy',
    step=0.01,
    verbose=True,
    shuffle_data=True,
    momentum=0.99,
    nesterov=True,
)

network.architecture()

network.train(data_train, target_train, data_test, target_test, epochs=1)

plots.error_plot(network)

target_predicted = network.predict(data_test).argmax(axis=1)
target_test = np.asarray(target_test.argmax(axis=1)).reshape(len(target_test))
print(metrics.classification_report(target_test, target_predicted))

score = metrics.accuracy_score(target_test, target_predicted)
print("Validation accuracy: {:.2%}".format(score))