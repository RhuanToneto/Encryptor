#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
#include <windows.h>

void setConsoleUTF8() {
    SetConsoleOutputCP(65001);
}

std::string criptografar(const std::string& texto, int chave) {
    std::string resultado = "";
    for (char c : texto) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            resultado += (c - base + chave) % 26 + base;
        } else {
            resultado += c;
        }
    }
    return resultado;
}

std::string descriptografar(const std::string& texto, int chave) {
    return criptografar(texto, 26 - chave);
}

std::string lerArquivo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return "";
    }
    std::string conteudo((std::istreambuf_iterator<char>(arquivo)), std::istreambuf_iterator<char>());
    arquivo.close();
    return conteudo;
}

void escreverArquivo(const std::string& nomeArquivo, const std::string& conteudo) {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita!" << std::endl;
        return;
    }
    arquivo << conteudo;
    arquivo.close();
}

void exibirAjuda() {
    std::cout << "\n===== Ajuda =====\n";
    std::cout << "1. Criptografar Mensagem: Criptografa uma mensagem fornecida pelo usuário.\n";
    std::cout << "2. Descriptografar Mensagem: Descriptografa uma mensagem fornecida pelo usuário.\n";
    std::cout << "3. Criptografar Arquivo: Criptografa o conteúdo de um arquivo.\n";
    std::cout << "4. Descriptografar Arquivo: Descriptografa o conteúdo de um arquivo.\n";
    std::cout << "5. Ver Histórico: Exibe o histórico de operações realizadas.\n";
    std::cout << "6. Teste de Segurança: Verifica se uma mensagem pode ser descriptografada corretamente.\n";
    std::cout << "7. Sair: Sai do programa.\n";
    std::cout << "Digite a opção desejada e pressione Enter.\n";
}

void exibirHistorico(const std::vector<std::string>& historico) {
    std::cout << "\n===== Histórico de Operações =====\n";
    for (const std::string& operacao : historico) {
        std::cout << operacao << std::endl;
    }
}

int main() {
    setConsoleUTF8();
    std::vector<std::string> historico;
    while (true) {
        int opcao;
        std::cout << "\nEscolha uma opção:\n";
        std::cout << "1. Criptografar Mensagem\n";
        std::cout << "2. Descriptografar Mensagem\n";
        std::cout << "3. Criptografar Arquivo\n";
        std::cout << "4. Descriptografar Arquivo\n";
        std::cout << "5. Ver Histórico\n";
        std::cout << "6. Teste de Segurança\n";
        std::cout << "7. Sair\n";
        std::cout << "8. Ajuda\n";
        std::cout << "Opção: ";
        std::cin >> opcao;
        std::cin.ignore();

        if (opcao == 7) {
            std::cout << "Saindo..." << std::endl;
            break;
        }

        if (opcao == 8) {
            exibirAjuda();
            continue;
        }

        std::string mensagem, nomeArquivo, resultado;
        int chave;

        std::string criptografada;

        switch (opcao) {
            case 1:
                std::cout << "Digite a mensagem: ";
                std::getline(std::cin, mensagem);

                std::cout << "Digite a chave (0-25): ";
                std::cin >> chave;
                std::cin.ignore();

                if (chave < 0 || chave > 25) {
                    std::cout << "Chave inválida! Deve estar entre 0 e 25." << std::endl;
                    continue;
                }

                resultado = criptografar(mensagem, chave);
                std::cout << "Mensagem criptografada: " << resultado << std::endl;
                historico.push_back("Criptografada: " + mensagem + " -> " + resultado);
                break;

            case 2:
                std::cout << "Digite a mensagem: ";
                std::getline(std::cin, mensagem);

                std::cout << "Digite a chave (0-25): ";
                std::cin >> chave;
                std::cin.ignore();

                if (chave < 0 || chave > 25) {
                    std::cout << "Chave inválida! Deve estar entre 0 e 25." << std::endl;
                    continue;
                }

                resultado = descriptografar(mensagem, chave);
                std::cout << "Mensagem descriptografada: " << resultado << std::endl;
                historico.push_back("Descriptografada: " + mensagem + " -> " + resultado);
                break;

            case 3:
                std::cout << "Digite o nome do arquivo: ";
                std::getline(std::cin, nomeArquivo);

                mensagem = lerArquivo(nomeArquivo);

                if (mensagem.empty()) {
                    std::cout << "Falha ao ler o arquivo ou arquivo vazio!" << std::endl;
                    continue;
                }

                std::cout << "Digite a chave (0-25): ";
                std::cin >> chave;
                std::cin.ignore();

                if (chave < 0 || chave > 25) {
                    std::cout << "Chave inválida! Deve estar entre 0 e 25." << std::endl;
                    continue;
                }

                resultado = criptografar(mensagem, chave);
                escreverArquivo(nomeArquivo, resultado); 
                std::cout << "Arquivo criptografado com sucesso!" << std::endl;
                historico.push_back("Arquivo criptografado: " + nomeArquivo);
                break;

            case 4:
                std::cout << "Digite o nome do arquivo: ";
                std::getline(std::cin, nomeArquivo);

                mensagem = lerArquivo(nomeArquivo);

                if (mensagem.empty()) {
                    std::cout << "Falha ao ler o arquivo ou arquivo vazio!" << std::endl;
                    continue;
                }

                std::cout << "Digite a chave (0-25): ";
                std::cin >> chave;
                std::cin.ignore();

                if (chave < 0 || chave > 25) {
                    std::cout << "Chave inválida! Deve estar entre 0 e 25." << std::endl;
                    continue;
                }

                resultado = descriptografar(mensagem, chave);
                escreverArquivo(nomeArquivo, resultado); 
                std::cout << "Arquivo descriptografado com sucesso!" << std::endl;
                historico.push_back("Arquivo descriptografado: " + nomeArquivo);
                break;

            case 5:
                exibirHistorico(historico);
                break;

            case 6:
                std::cout << "Digite a mensagem original: ";
                std::getline(std::cin, mensagem);

                std::cout << "Digite a mensagem criptografada: ";
                std::getline(std::cin, criptografada);

                std::cout << "Digite a chave usada para criptografar (0-25): ";
                std::cin >> chave;
                std::cin.ignore();

                if (chave < 0 || chave > 25) {
                    std::cout << "Chave inválida! Deve estar entre 0 e 25." << std::endl;
                    continue;
                }

                resultado = criptografar(mensagem, chave);
                if (resultado == criptografada) {
                    std::cout << "Teste de segurança bem-sucedido: A mensagem foi criptografada corretamente." << std::endl;
                } else {
                    std::cout << "Teste de segurança falhou: A mensagem não foi criptografada corretamente." << std::endl;
                }
                break;

            default:
                std::cout << "Opção inválida!" << std::endl;
                break;
        }
    }

    return 0;
}
