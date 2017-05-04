// Copyright (c) 2013-2017 Irreverent Bits
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#import <Foundation/Foundation.h>


@class IBStringValidator;

/**
 Block type used for validVlock and invalidBlock state change callbacks.
 */
typedef void(^IBStringValidatorBlock)(IBStringValidator* validator);


/**
 IBStringValidator provides facilities for checking strings against validity criteria for
 string length and regular expression matching. Validity state is stored for submitted
 strings so that changes in validity for a given string can be tracked and reacted to.
 
 Strings to be checked and tracked should be submitted via updateValidityForString: every
 time the string changes. Only strings submitted via this method update the string validator's stored state.
 
 Observe the validity boolean properties isValid, isLengthValid and isRegexValid to recieve live updates
 about the validity of strings submitted via updateValidityForString:.
 
 Use isValidForString:, isLengthValidForString: and isRegexValidForString: to test whether a
 string would be considered valid for the string validator's criteria. Strings submitted via
 these methods do not alter the string validator's stored state.
 
 IBStringValidator does not store a copy or reference of strings submitted to it. To keep the validity
 state current, submit a string every time the string changes. This will also insure that submitted
 validity blocks are invoked when the validity state changes from valid to invalid or vice-versa.
 */
@interface IBStringValidator : NSObject

/**
 The minimum length string that passes validation. If nil, no check is made for
 a minimum length value.
 @see maxLength
 */
@property (nonatomic, strong) NSNumber *minLength;

/**
 The maximum length string that passes validation. If nil, no check is made for
 a maximum length value.
 @see minLength
 */
@property (nonatomic, strong) NSNumber *maxLength;

/**
 The regular expression pattern used to validate strings. If nil, no check is
 made for a specific string pattern.
 */
@property (nonatomic, strong) NSString *regexPattern;

/**
 validBlock is called once when first set if the state of the string validator is
 valid. After this it is called whenever the state of the string validator changes
 from invalid to valid.
 @see invalidBlock
 */
@property (nonatomic, strong) IBStringValidatorBlock validBlock;

/**
 invalidBlock is called once when first set if the state of the string validator is
 invalid. After this it is called whenver the state of the string validator changes
 from valid to invalid.
 @see validBlock
 */
@property (nonatomic, strong) IBStringValidatorBlock invalidBlock;

/**
 Indicates whether the last string submitted via updateValidityForString: was valid or not.
 @see isLengthValid
 @see isRegexValid
 */
@property (nonatomic, readonly, assign) BOOL isValid;

/**
 Indicates whether the last string submitted via updateValidityForString: had a valid length or not.
 Note, this is determined using the minLength and maxLength values. If regexPattern imposes a limit
 to the string length, isLengthValid will not reflect the restrictions imposed by the regular expression.
 @see isValid
 @see isRegexValid
 */
@property (nonatomic, readonly, assign) BOOL isLengthValid;

/**
 Indicates whether the last string submitted via updateValidityForString: passed the regular expression
 specified by regexPattern.
 @see isValid
 @see isLengthValid
 */
@property (nonatomic, readonly, assign) BOOL isRegexValid;

/**
 Creates a new string validator with the provided validation requirements.
 @param minLength The minimum length for a valid string.
 @param maxLength The maximum length for a valid string.
 @param regexPattern The regular expression pattern that must pass for a valid string.
 @return An initialized string validator.
 */
- (id)initWithValidationMinLength:(NSNumber*)minLength
						maxLength:(NSNumber*)maxLength
					 regexPattern:(NSString*)regexPattern;

/**
 Convenience method to setup acceptance criteria in one code line.
 @param minLength Optional. If set as nil, then no minimum length constraint is applied to determine validity.
 @param maxLength Optional. If set as nil, then no maximum length constraint is applied to determine validity.
 @param regexPattern Optional. If set as nil, then no regex constraint is applied to determine validity.
 */
- (void)setValidationMinLength:(NSNumber*)minLength
					 maxLength:(NSNumber*)maxLength
				  regexPattern:(NSString*)regexPattern;

/**
 Submit a new string for validity testing. This IBStringValidator's state
 will be updated to reflect the result of the validity test of the provided string.
 @param testString The string to test.
 */
- (void)updateValidityForString:(NSString*)testString;

/**
 Submit a string to test against all of the string validator's acceptance criteria.
 This method does not alter the validity state of the string validator.
 @param testString The string to test.
 @return YES if the testString is valid, otherwise NO.
 @see isLengthValidForString:
 @see isRegexValidForString:
 */
- (BOOL)isValidForString:(NSString*)testString;

/**
 Submit a string to test against the string validator's length constraints.
 Note, the string could still be invalid for the string validator's regular
 expression even though it is valid for the length constraints.
 This method does not alter the validity state of the string validator.
 @param testString The string to test.
 @return YES if the testString is valid, otherwise NO.
 @see isValidForString:
 @see isRegexValidForString:
 */
- (BOOL)isLengthValidForString:(NSString*)testString;

/**
 Submit a string to test against the string validator's regular expression constraints.
 Note, the string could still be invalid for the string validator's length
 constraints even though it is valid for the regular expression.
 This method does not alter the validity state of the string validator.
 @param testString The string to test.
 @return YES if the testString is valid, otherwise NO.
 @see isValidForString:
 @see isLengthValidForString:
 */
- (BOOL)isRegexValidForString:(NSString*)testString;

@end
