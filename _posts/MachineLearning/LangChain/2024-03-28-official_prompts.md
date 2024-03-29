---
title: Official Prompts
tags: LangChain
---

<!--more-->

LangChain 코드에서 내부적으로 사용하는 prompt들에 대하여 기능 및 사용처 등을 적어놓고 나중에 필요한 경우가 오면 baseline으로 사용하면 좋을 것 같다.


- [`langchain.chains.openai_functions.tagging._TAGGING_TEMPLATE`](https://github.com/langchain-ai/langchain/blob/fdfb51ad8daffa1e6e5c6889fd71627697de178e/libs/langchain/langchain/chains/openai_functions/tagging.py#L23)
    ```python
    _TAGGING_TEMPLATE = """Extract the desired information from the following passage.

    Only extract the properties mentioned in the 'information_extraction' function.

    Passage:
    {input}
    """
    ```

    ```python
    def create_tagging_chain(
        schema: dict,
        llm: BaseLanguageModel,
        prompt: Optional[ChatPromptTemplate] = None,
        **kwargs: Any,
    ) -> Chain:
        """Creates a chain that extracts information from a passage
        based on a schema.

        Args:
            schema: The schema of the entities to extract.
            llm: The language model to use.

        Returns:
            Chain (LLMChain) that can be used to extract information from a passage.
        """
        function = _get_tagging_function(schema)
        prompt = prompt or ChatPromptTemplate.from_template(_TAGGING_TEMPLATE)
        output_parser = JsonOutputFunctionsParser()
        llm_kwargs = get_llm_kwargs(function)
        chain = LLMChain(
            llm=llm,
            prompt=prompt,
            llm_kwargs=llm_kwargs,
            output_parser=output_parser,
            **kwargs,
        )
        return chain
    ```

    1. 용도
        - 주어진 텍스트와 schema로부터 value를 추론하는 역할을 할 때 사용한다.
    2. 참고사항
        - 참고할 정보를 `context`라고 지칭하는 게 일반적이라고 생각했는데 여기에선 `passage`라는 단어를 사용하였다. `passage`가 대세인걸까?
        - `... from the following passage ... Passage: ...` 이런 구조는 자주 써먹을 수 있을 것 같다.
