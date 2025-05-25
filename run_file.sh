FILENAME="main"

gcc "${FILENAME}.c" -o "${FILENAME}"

if [ $? -eq 0 ]; then
    echo "Compilacao deu certo."
    ./"${FILENAME}"
    echo -e ""
else
    echo "Compilacao falhou."
fi